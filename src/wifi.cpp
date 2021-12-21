#include "eeprom.h"
#include "rtc.h"
#include "util.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IPAddress.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <string.h>
#include <xrstf_arduino_util.h>
#include <xrstf_util.h>

namespace wifi {
	bool connected;
	IPAddress localIP;

	bool enabled(eeprom::data *config) {
		return config->enableWifi && strlen(config->ssid) > 0 && strlen(config->password) > 0;
	}

	void updateClock() {
		if (!rtc::exists()) {
			return;
		}

		// setup NTP client
		WiFiUDP ntpUDP;
		NTPClient timeClient(ntpUDP, "de.pool.ntp.org");

		Serial.println("Attempting NTP update...");

		// fetch current UNIX timestamp
		timeClient.begin();
		if (timeClient.update()) {
			time_t epoch = timeClient.getEpochTime();

			tmElements_t tm;
			breakTime(epoch, tm);
			rtc::set(tm);

			Serial.println("NTP update OK.");
			xrstf::blinkLED(LED_PIN, 5, 150);
		}
		timeClient.end();
	}

	void connect(eeprom::data *config) {
		if (!connected && enabled(config)) {
			xrstf::serialPrintf("Connecting to Wifi '%s'...\n", config->ssid);

			char buf[128] = {0};
			sprintf(buf, "froy-%s", config->deviceName);

			WiFi.hostname(buf);
			WiFi.setAutoReconnect(true);
			WiFi.begin(config->ssid, config->password);

			int attempts = 150; // 150 times 200ms = 30s timeout
			while (attempts > 0 && WiFi.status() != WL_CONNECTED) {
				delay(200);
				attempts--;
			}

			if (WiFi.status() != WL_CONNECTED) {
				Serial.println("Connection failed :(");
				return;
			}

			localIP = WiFi.localIP();

			xrstf::serialPrintf("Connection established, my IP is %s!\n", localIP.toString().c_str());
			connected = true;

			updateClock();
		}
	}

	void disconnect() {
		if (connected) {
			WiFi.disconnect(true);
			Serial.println("Wifi disconnected.");
			connected = false;
		}
	}
} // namespace wifi
