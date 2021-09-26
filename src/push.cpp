#include "config.h"
#include "eeprom.h"
#include "multimeter.h"
#include "ota.h"
#include "sensor.h"
#include "util.h"
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <xrstf_arduino_util.h>
#include <xrstf_util.h>

char otaConstraintResponse[64] = {0};

bool pushHTTP(eeprom::data *config, String body) {
	WiFiClient wifiClient;
	HTTPClient httpClient;

	if (!httpClient.begin(wifiClient, config->pushURL)) {
		Serial.println("Error: Failed to setup HTTP client.");
		return false;
	}

	char ua[128];
	memset(ua, 0, sizeof(ua));
	sprintf(ua, "froy-%s/%s", config->deviceName, FROY_VERSION);

	httpClient.addHeader("Content-Type", "application/json");
	httpClient.setUserAgent(ua);
	httpClient.setTimeout(10000);
	httpClient.setReuse(false);

	int responseCode = httpClient.POST(body.c_str());
	if (responseCode < 0) {
		xrstf::serialPrintf("Error: Request failed: %s\n", httpClient.errorToString(responseCode).c_str());
	} else {
		xrstf::serialPrintf("OK: Response code: %d\n", responseCode);
	}

	if (responseCode != HTTP_CODE_OK) {
		return false;
	}

	return eeprom::updateFromJSON(config, httpClient.getString(), otaConstraintResponse);
}

bool pushHTTPS(eeprom::data *config, String body) {
	BearSSL::WiFiClientSecure client;

	if (eeprom::hasFingerprint(config->pushFingerprint)) {
		if (!client.setFingerprint((uint8_t *)config->pushFingerprint)) {
			Serial.println("failed setting fingerprint");
		}
	} else {
		client.setInsecure();
	}

	HTTPClient httpClient;
	if (!httpClient.begin(client, config->pushURL)) {
		Serial.println("Error: Failed to setup HTTP client.");
		return false;
	}

	char ua[32];
	memset(ua, 0, sizeof(ua));
	sprintf(ua, "froy/%s", FROY_VERSION);

	httpClient.addHeader("Content-Type", "application/json");
	httpClient.setUserAgent(ua);

	int responseCode = httpClient.POST(body.c_str());
	if (responseCode < 0) {
		xrstf::serialPrintf("Error: Request failed: %s\n", httpClient.errorToString(responseCode).c_str());
	} else {
		xrstf::serialPrintf("OK: Response code: %d\n", responseCode);
	}

	if (responseCode != HTTP_CODE_OK) {
		return false;
	}

	return eeprom::updateFromJSON(config, httpClient.getString(), otaConstraintResponse);
}

bool pushMeasurement(eeprom::data *config, multimeter::measurement *measurement) {
	StaticJsonDocument<256> doc;

	doc["deviceName"]         = config->deviceName;
	doc["appVersion"]         = FROY_VERSION;
	doc["sensorType"]         = sensor::typeName(config->sensorType);
	doc["temperature"]        = measurement->sensor.temperature;
	doc["pressure"]           = measurement->sensor.pressure;
	doc["humidity"]           = measurement->sensor.humidity;
	doc["temperatureOffset"]  = config->temperatureOffset;
	doc["pressureOffset"]     = config->pressureOffset;
	doc["humidityOffset"]     = config->humidityOffset;
	doc["temperatureRetries"] = measurement->sensor.temperatureRetries;
	doc["pressureRetries"]    = measurement->sensor.pressureRetries;
	doc["humidityRetries"]    = measurement->sensor.humidityRetries;
	doc["duration"]           = measurement->duration;
	doc["battery"]            = measurement->battery;

	String body;
	serializeJson(doc, body);

	xrstf::serialPrintf("Pushing measurement to %s\n", config->pushURL);

	if (xrstf::startsWith(config->pushURL, "https://")) {
		return pushHTTPS(config, body);
	} else {
		return pushHTTP(config, body);
	}
}

bool handlePushMode(eeprom::data *config) {
	if (config->enableLED) {
		enableLED();
	}

	multimeter::measurement m;
	multimeter::read(&m, config);

	pushMeasurement(config, &m);

	if (config->enableLED) {
		disableLED();
	}

	if (*otaConstraintResponse) {
		String url(config->otaURL);
		String constraint(otaConstraintResponse);

		ota::update(url, constraint, config->otaFingerprint);
	}

	return true;
}
