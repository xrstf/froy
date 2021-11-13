#include "eeprom.h"
#include "util.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IPAddress.h>
#include <string.h>
#include <xrstf_arduino_util.h>
#include <xrstf_util.h>

namespace wifi {
	bool connected;
	IPAddress localIP;

	bool enabled(eeprom::data *config) {
		return config->enableWifi && strlen(config->ssid) > 0 && strlen(config->password) > 0;
	}

	void connect(eeprom::data *config) {
		if (!connected && enabled(config)) {
			xrstf::serialPrintf("Connecting to Wifi '%s'...\n", config->ssid);

			char buf[128] = {0};
			sprintf(buf, "froy-%s", config->deviceName);

			WiFi.hostname(buf);
			WiFi.setAutoReconnect(true);
			WiFi.begin(config->ssid, config->password);

			int attempts = 60; // 60 times 500ms = 30s timeout
			while (attempts > 0 && WiFi.status() != WL_CONNECTED) {
				delay(500);
				attempts--;
			}

			if (WiFi.status() != WL_CONNECTED) {
				Serial.println("Connection failed :(");
				return;
			}

			localIP = WiFi.localIP();

			xrstf::serialPrintf("Connection established, my IP is %s!\n", localIP.toString().c_str());
			connected = true;
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
