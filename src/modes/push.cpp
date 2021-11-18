#include "config.h"
#include "eeprom.h"
#include "multimeter.h"
#include "ota.h"
#include "sensor.h"
#include "util.h"
#include "wifi.h"
#include "cli.h"
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <xrstf_arduino_util.h>
#include <xrstf_util.h>

char otaConstraintResponse[64] = {0};

bool pushFile(eeprom::data *config, const char* identifier, File *fs) {
	WiFiClient wifiClient;
	HTTPClient httpClient;

	if (!httpClient.begin(wifiClient, config->pushURL)) {
		Serial.println("Error: Failed to setup HTTP client.");
		return false;
	}

	char ua[128];
	memset(ua, 0, sizeof(ua));
	sprintf(ua, "froy-%s/%s", config->deviceName, FROY_VERSION);

	httpClient.addHeader("Content-Type", "application/octet-stream");
	httpClient.addHeader("Froy-Device", config->deviceName);
	httpClient.addHeader("Froy-Version", FROY_VERSION);
	httpClient.addHeader("Froy-Series", identifier);
	httpClient.setUserAgent(ua);
	httpClient.setTimeout(10000);
	httpClient.setReuse(false);

	int responseCode = httpClient.sendRequest("POST", fs, fs->size());
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

bool pushMeasurement(eeprom::data *config, multimeter::measurement *measurement) {
	StaticJsonDocument<384> doc;

	// shorter keys do not reduce ArduinoJSON's memory usage, but still keeps
	// the resulting JSON document smaller. Smaller means less RAM and faster
	// network roundtrips, so it's good(tm).

	/* deviceName */ doc["dn"]         = config->deviceName;
	/* appVersion */ doc["av"]         = FROY_VERSION;
	/* sensorType */ doc["st"]         = sensor::typeName(config->sensorType);
	/* temperature */ doc["t"]         = measurement->sensor.temperature;
	/* pressure */ doc["p"]            = measurement->sensor.pressure;
	/* humidity */ doc["h"]            = measurement->sensor.humidity;
	/* temperatureOffset */ doc["to"]  = config->temperatureOffset;
	/* pressureOffset */ doc["po"]     = config->pressureOffset;
	/* humidityOffset */ doc["ho"]     = config->humidityOffset;
	/* temperatureRetries */ doc["tr"] = measurement->sensor.temperatureRetries;
	/* pressureRetries */ doc["pr"]    = measurement->sensor.pressureRetries;
	/* humidityRetries */ doc["hr"]    = measurement->sensor.humidityRetries;
	/* duration */ doc["d"]            = measurement->duration;
	/* battery */ doc["b"]             = measurement->battery;
	/* batteryRaw */ doc["br"]         = measurement->batteryRaw;

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

	// in this mode we always push a HTTP message out and
	// also use the time to establish the WiFi connect as the
	// delay to allow incoming CLI requests via Serial.
	wifi::connect(config);

	// check if a command was sent
	cli::handleCommand();

	// reload EEPROM data, in case the user disabled sleep mode
	eeprom::load(config);

	// push mode got disabled
	if (config->sleepMinutes == 0) {
		disableLED();
		return false; // go into standby mode
	}

	// if we could not connect, go back to sleep
	if (!wifi::connected) {
		return true;
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

	// Because the HTTP response to a push message can include
	// a configuration snippet to reconfigure this device
	// remotely, the push mode can also be disabled. Hence
	// after handlePushMode() is done, config->sleepMinutes
	// could be 0 and we must not attempt to go to deep sleep.
	if (config->sleepMinutes > 0) {
		delay(100);
		return true;
	}

	return false; // go into standby mode
}
