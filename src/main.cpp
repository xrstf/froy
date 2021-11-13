/*
 To flash this, choose the following settings in the Arduino IDE:

     - board:        Generic ESP8266 Board
     - upload speed: 115200
     - reset mode:   "dtr (aka nodemcu)" for mini-reset-circuit
                                     "no dtr (aka ck)" for kevin's circuit

 To ensure EEPROM works:

     - flash frequency: 26Mhz
     - flash size:      2MB (FS: 64KB)

 The remaining things can be left as-is.
*/

#include "cli.h"
#include "config.h"
#include "eeprom.h"
#include "log.h"
#include "multimeter.h"
#include "push.h"
#include "sensor.h"
#include "util.h"
#include "webserver.h"
#include "wifi.h"
#include <xrstf_arduino_util.h>

void runSleepMode(eeprom::data *config, long bootTime) {
	bool sleep = false;

	// if a series name is set, we're in data logging mode
	if (strlen(config->seriesName) > 0) {
		sleep = handleDataLoggingMode(config);
	} else if (config->sleepMinutes > 0) {
		sleep = handlePushMode(config);
	}

	if (sleep) {
		// deduct the time spent from the sleep time
		long delayed     = millis() - bootTime;
		long sleepMillis = (config->sleepMinutes * 60 * 1000) - delayed;

		xrstf::serialPrintf("Nighty night, see you in %ld seconds.\n", (sleepMillis / 1000));

		ESP.deepSleep(sleepMillis * 1000);
	}
}

void setup() {
	long bootTime = millis();

	xrstf::setupLED(LED_PIN);
	multimeter::setup();
	cli::setup();
	eeprom::init();

	LOAD_EEPROM(data);

	if (data.sleepMinutes > 0) {
		runSleepMode(&data, bootTime); // this function _usually_ doesn't return
	}

	wifi::connect(&data);
	webserver::setup();
	webserver::start();

	if (data.enableLED) {
		xrstf::blinkLED(LED_PIN, 3, 200);
	}
}

void loop() {
	if (needsRestart()) {
		ESP.restart();
	}

	cli::handleCommand();
	webserver::handleRequests();
}
