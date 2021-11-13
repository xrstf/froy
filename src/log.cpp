#include "log.h"
#include "cli.h"
#include "multimeter.h"
#include "rtc.h"
#include "wifi.h"
#include "datalogger.h"
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
		return false;
	}

	// if we have reached the number of datapoints to make, go to sleep
	if (config->maxSeriesPoints > 0 && config->remainingSeriesPoints == 0) {
		return true;
	}

	// ensure clock is good
	setupClock(config);

	// get current date and time
	tmElements_t now;
	rtc::read(now); // this can still fail, if no chip is present or NTP failed

	// make a measurement
	multimeter::measurement m;
	multimeter::read(&m, config);

	// log it to memory
	Datalogger dl(LittleFS, "m");
	if (!dl.begin()) {
		Serial.println("Failed to init LittleFS.");
		return true; // good luck next time, go back to sleep
	}

	char timestamp[32];
	sprintf(timestamp, "%04d-%02d-%02dT%02d:%02d:%02d", rtc::decodeYear(now.Year), now.Month, now.Day, now.Hour, now.Minute, now.Second);

	char data[64];
	sprintf(data, "%s;%.2f;%.2f;%.2f;%d", timestamp, m.sensor.temperature, m.sensor.humidity, m.sensor.pressure, m.batteryRaw);

	dl.appendData(config->seriesName, data);
	dl.end();

	// we're done, let's go to sleep again
	return true;
}
