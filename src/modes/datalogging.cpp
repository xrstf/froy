#include "modes/datalogging.h"
#include "cli.h"
#include "datalogger.h"
#include "modes/push.h"
#include "multimeter.h"
#include "rtc.h"
#include "util.h"
#include "wifi.h"
#include <xrstf_arduino_util.h>

void setupClock(eeprom::data *config) {
	if (!rtc::exists()) {
		return;
	}

	tmElements_t tm;
	if (rtc::read(tm)) {
		return; // all OK
	}

	// try to connect (if WiFi is enabled and we have credentials set);
	// after connecting, the code will automatically attempt an NTP update.
	wifi::connect(config);
	wifi::disconnect();
}

void batchUpload(eeprom::data *config, Datalogger *dl) {
	char filename[32];
	dl->metricFilename(filename, config->seriesName);

	// breaking the Datalogger abstraction here, because I do not know
	// how to return a File object without it getting GC'ed... sorry.
	File f = LittleFS.open(filename, "r");
	if (!f) {
		Serial.println("Failed to open file.");
		return;
	}

	wifi::connect(config);
	if (!wifi::connected) {
		f.close();
		return;
	}

	// try to upload the file
	Serial.println("Pushing file...");
	bool success = pushFile(config, config->seriesName, &f);
	f.close();

	// if this was successful, trim the current file down to 0
	if (success) {
		Serial.println("Push successful, cleaning up.");
		dl->removeMetric(config->seriesName);

		config->pointsSampled = 0;
		eeprom::save(config);
	}
}

size_t dumpFloat(char *buf, float value) {
	memcpy(buf, (char *)&value, sizeof(value));
	return sizeof(value);
}

// dumpTimestamp only stores the time in xrstf epoch,
// which is hereby defined as "seconds since 2020-01-01 midnight UTC";
// this shifts the time range to be my lifetime and
// allows me to save 4 more bytes, cause we do not need 64 bit anymore.
size_t dumpTimestamp(char *buf, time_t value) {
	uint32_t epoch = (uint32_t) (value - 1577836800);
	memcpy(buf, (char *)&epoch, sizeof(epoch));
	return sizeof(epoch);
}

size_t dumpUint16(char *buf, uint16_t value) {
	memcpy(buf, (char *)&value, sizeof(value));
	return sizeof(value);
}

bool handleDataLoggingMode(eeprom::data *config) {
	// in this mode, we do not connect to the WiFi, so we must wait a
	// short moment to give the user (me! you!) a chance to send a CLI
	// command to jump out of sleep mode;
	uint32_t waitUntil = millis() + 2 * 1000; // 2 seconds
	while (millis() < waitUntil) {
		cli::handleCommand();
		yield();
	}

	// reload EEPROM data, in case the user disabled sleep mode
	eeprom::load(config);

	// if the series name was removed, we end datalogging mode and
	// go back into standby mode
	if (config->sleepMinutes == 0 || strlen(config->seriesName) == 0) {
		Serial.println("Data logging mode disabled, going into stand-by mode...");
		return false;
	}

	// if we have reached the number of datapoints to make, go to sleep
	if (config->maxSeriesPoints > 0 && config->pointsSampled >= config->maxSeriesPoints) {
		xrstf::serialPrintf("Reached desired number (%d) of data points, going back to sleep.\n", config->pointsSampled);
		return true;
	}

	// ensure clock is good
	setupClock(config);

	if (config->enableLED) {
		enableLED();
	}

	// get current date and time
	tmElements_t now;
	rtc::read(now); // this can still fail, if no chip is present or NTP failed

	// make a measurement
	Serial.println("Performing measurement...");
	multimeter::measurement m;
	multimeter::read(&m, config);

	// we're supposed to just perform a certain number of measurements, or we are supposed
	// to make batch uploads; only in either of these cases do we actually count the samples,
	// as not counting saves one eeprom::save() cycle.
	if (config->maxSeriesPoints > 0 || config->batchUploadSize > 0) {
		config->pointsSampled++;
		eeprom::save(config);
	}

	// log it to memory
	Datalogger dl(LittleFS, "m");
	if (!dl.begin()) {
		Serial.println("Failed to init LittleFS.");
		disableLED();
		return true; // good luck next time, go back to sleep
	}

	// init new files with a version number
	if (!dl.hasMetric(config->seriesName)) {
		dl.appendData(config->seriesName, "V1");
	}

	// below is what we define as "Version 1" of our binary data format

	// log data as raw bytes with a fixed length, so we save
	// as much space as possible; note that dumpTimestamp trims the
	// time down to 4 bytes!
	// ts (4b) + temp (4b) + humidity (4b) + pressure (4b) + batteryRaw (2b) = 18 byte
	char data[18];
	memset(data, 0x0, sizeof(data));

	size_t pos = 0;
	pos += dumpTimestamp(data + pos, makeTime(now));
	pos += dumpFloat(data + pos, m.sensor.temperature);
	pos += dumpFloat(data + pos, m.sensor.humidity);
	pos += dumpFloat(data + pos, m.sensor.pressure);
	pos += dumpUint16(data + pos, m.batteryRaw);

	dl.appendData(config->seriesName, data, pos);
	Serial.println("Measurement logged.");

	// check if we need to try a batch upload now
	if (config->batchUploadSize > 0 && config->pointsSampled >= config->batchUploadSize) {
		Serial.println("Reached batch size, attempting upload...");
		batchUpload(config, &dl);
	}

	dl.end();

	disableLED();

	// we're done, let's go to sleep again
	return true;
}
