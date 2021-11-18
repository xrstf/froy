#include "modes/datalogging.h"
#include "cli.h"
#include "datalogger.h"
#include "modes/push.h"
#include "multimeter.h"
#include "rtc.h"
#include "util.h"
#include "wifi.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <xrstf_arduino_util.h>

void setupClock(eeprom::data *config) {
	if (!rtc::exists()) {
		return;
	}

	tmElements_t tm;
	if (rtc::read(tm)) {
		return; // all OK
	}

	// we need WiFi for NTP
	if (!wifi::enabled(config)) {
		return;
	}

	// we have WiFi credentials, so we can connect!
	wifi::connect(config);
	if (!wifi::connected) {
		return;
	}

	// setup NTP client
	WiFiUDP ntpUDP;
	NTPClient timeClient(ntpUDP);

	// fetch current UNIX timestamp
	timeClient.begin();
	if (timeClient.update()) {
		time_t epoch = timeClient.getEpochTime();
		breakTime(epoch, tm);
		rtc::set(tm);
		xrstf::blinkLED(LED_PIN, 5, 200);
	}
	timeClient.end();

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

	char timestamp[32];
	sprintf(timestamp, "%04d%02d%02d%02d%02d%02d", rtc::decodeYear(now.Year), now.Month, now.Day, now.Hour, now.Minute, now.Second);

	char data[64];
	sprintf(data, "%s;%.2f;%.2f;%.2f;%d", timestamp, m.sensor.temperature, m.sensor.humidity, m.sensor.pressure, m.batteryRaw);

	dl.appendData(config->seriesName, data);
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
