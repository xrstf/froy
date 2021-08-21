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
#include "multimeter.h"
#include "push.h"
#include "sensor.h"
#include "util.h"
#include "webserver.h"
#include "wifi.h"
#include <xrstf_arduino_util.h>

void runSleepMode(struct eeprom::data *config, long bootTime) {
	// allow the user to disable the sleep mode if they're quick
	// (they have the time it takes for the ESP to connect to wifi)
	cli::handleCommand();

	// reload EEPROM data, in case the user disabled sleep mode
	eeprom::load(config);

	if (config->sleepMinutes > 0) {
		handlePushMode(config);

		// Because the HTTP response to a push message can include
		// a configuration snippet to reconfigure this device
		// remotely, the push mode can also be disabled. Hence
		// after handlePushMode() is done, config->sleepMinutes
		// could be 0 and we must not attempt to go to deep sleep.
		if (config->sleepMinutes > 0) {
			delay(100);

			// deduct the time spent from the sleep time
			long delayed     = millis() - bootTime;
			long sleepMillis = (config->sleepMinutes * 60 * 1000) - delayed;

			xrstf::serialPrintf("Nighty night, see you in %ld seconds.\n", (sleepMillis / 1000));

			ESP.deepSleep(sleepMillis * 1000);
		}
	}
}

void setup() {
	long bootTime = millis();

	xrstf::setupLED(LED_PIN);
	multimeter::setup();
	cli::setup();
	eeprom::init();
	wifi::connect();

	LOAD_EEPROM(data);

	if (data.sleepMinutes > 0) {
		runSleepMode(&data, bootTime); // this function usually doesn't return
	}

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
