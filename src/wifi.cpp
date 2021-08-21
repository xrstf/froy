#include "eeprom.h"
#include "util.h"
#include <xrstf_util.h>
#include <xrstf_arduino_util.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IPAddress.h>
#include <string.h>

namespace wifi {
	bool connected;
	IPAddress localIP;

	void connect() {
		LOAD_EEPROM(data);

		if (data.enableWifi && strlen(data.ssid) > 0 && strlen(data.password) > 0) {
			xrstf::serialPrintf("Connecting to Wifi '%s'...\n", data.ssid);

			char buf[128] = {0};
			sprintf(buf, "froy-%s", data.deviceName);

			WiFi.hostname(buf);
			WiFi.setAutoReconnect(true);
			WiFi.begin(data.ssid, data.password);

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
}
