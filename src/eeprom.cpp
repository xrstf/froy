#include "eeprom.h"
#include "sensor.h"
#include "util.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <xrstf_arduino_util.h>
#include <xrstf_util.h>

namespace eeprom {
	const char signature[] = {'F', 'R', 'O', 'Y'};

	struct signatureOnlyData {
		char signature[4];
		char version;
	};

	void migrateV1toV2() {
		dataV1 v1;
		EEPROM.begin(sizeof(dataV1));
		EEPROM.get(0, v1);
		EEPROM.end();

		data v2;
		v2.version           = 0x02;
		v2.enableWebserver   = v1.enableWebserver;
		v2.enableWifi        = v1.enableWifi;
		v2.enableLED         = v1.enableLED;
		v2.sensorType        = v1.sensorType;
		v2.sensorAddress     = v1.sensorAddress;
		v2.temperatureOffset = v1.temperatureOffset;
		v2.humidityOffset    = v1.humidityOffset;
		v2.pressureOffset    = v1.pressureOffset;
		v2.sleepMinutes      = v1.sleepMinutes;

		memcpy(v2.signature, signature, sizeof(v2.signature));
		memcpy(v2.deviceName, v1.deviceName, sizeof(v2.deviceName));
		memcpy(v2.pushURL, v1.pushURL, sizeof(v2.pushURL));
		memset(v2.pushFingerprint, 0x0, sizeof(v2.pushFingerprint));
		memset(v2.otaURL, 0x0, sizeof(v2.otaURL));
		memset(v2.otaFingerprint, 0x0, sizeof(v2.otaFingerprint));
		memcpy(v2.ssid, v1.ssid, sizeof(v2.ssid));
		memcpy(v2.password, v1.password, sizeof(v2.password));

		EEPROM.begin(sizeof(data));
		EEPROM.put(0, v2);
		EEPROM.end();
	}

	void migrateV2toV3() {
		dataV2 v2;
		EEPROM.begin(sizeof(dataV2));
		EEPROM.get(0, v2);
		EEPROM.end();

		data v3;
		v3.version               = 0x03;
		v3.enableWebserver       = v2.enableWebserver;
		v3.enableWifi            = v2.enableWifi;
		v3.enableLED             = v2.enableLED;
		v3.sensorType            = v2.sensorType;
		v3.sensorAddress         = v2.sensorAddress;
		v3.temperatureOffset     = v2.temperatureOffset;
		v3.humidityOffset        = v2.humidityOffset;
		v3.pressureOffset        = v2.pressureOffset;
		v3.sleepMinutes          = v2.sleepMinutes;
		v3.maxSeriesPoints       = 0;
		v3.remainingSeriesPoints = 0;

		memcpy(v3.signature, signature, sizeof(v3.signature));
		memcpy(v3.deviceName, v2.deviceName, sizeof(v3.deviceName));
		memcpy(v3.pushURL, v2.pushURL, sizeof(v3.pushURL));
		memcpy(v3.pushFingerprint, v2.pushFingerprint, sizeof(v3.pushFingerprint));
		memcpy(v3.otaURL, v2.otaURL, sizeof(v3.otaURL));
		memcpy(v3.otaFingerprint, v2.otaFingerprint, sizeof(v3.otaFingerprint));
		memcpy(v3.ssid, v2.ssid, sizeof(v3.ssid));
		memcpy(v3.password, v2.password, sizeof(v3.password));
		memcpy(v3.seriesName, 0x0, sizeof(v3.seriesName));

		EEPROM.begin(sizeof(data));
		EEPROM.put(0, v3);
		EEPROM.end();
	}

	/**
	 * migrate and/or set defaults
	 */
	void init() {
		signatureOnlyData sig;
		EEPROM.begin(sizeof(signatureOnlyData));
		EEPROM.get(0, sig);
		EEPROM.end();

		// no signature present yet, init current defaults
		if (strncmp(sig.signature, signature, sizeof(sig.signature)) != 0) {
			// this could be an old v1-style froy without a signature yet,
			// in this case the first byte is the EEPROM version and the
			// second is the bootstrapDone flag
			if (sig.signature[0] && sig.signature[1] == 0x01) {
				migrateV1toV2();
			} else {
				data d;
				setDefaults(&d);
				save(&d);
				return;
			}
		}

		if (sig.version == 0x02) {
			Serial.println("Migrating version 2 to 3...");
			migrateV2toV3();
		}
	}

	void setDefaults(data *d) {
		d->version               = VERSION;
		d->enableWebserver       = true;
		d->enableWifi            = false;
		d->enableLED             = true;
		d->sensorType            = 0x0;
		d->sensorAddress         = 0x76; // should work for most cheapo breakout boards
		d->temperatureOffset     = 0;
		d->humidityOffset        = 0;
		d->pressureOffset        = 0;
		d->sleepMinutes          = 0;
		d->maxSeriesPoints       = 0;
		d->remainingSeriesPoints = 0;
		strncpy(d->signature, signature, sizeof(d->signature));
		strncpy(d->deviceName, "froy", sizeof(d->deviceName));
		memset(d->pushURL, 0x0, sizeof(d->pushURL));
		memset(d->pushFingerprint, 0x0, sizeof(d->pushFingerprint));
		memset(d->otaURL, 0x0, sizeof(d->otaURL));
		memset(d->otaFingerprint, 0x0, sizeof(d->otaFingerprint));
		memset(d->ssid, 0x0, sizeof(d->ssid));
		memset(d->password, 0x0, sizeof(d->password));
		memcpy(d->seriesName, 0x0, sizeof(d->seriesName));
	}

	void load(data *d) {
		EEPROM.begin(sizeof(data));
		EEPROM.get(0, *d);
		EEPROM.end();
	}

	void save(data *d) {
		EEPROM.begin(sizeof(data));
		EEPROM.put(0, *d);
		EEPROM.end();
	}

	bool updateFromJSON(data *config, const String &json, char *otaConstraintOut) {
		if (json.length() == 0) {
			return true;
		}

		StaticJsonDocument<384> doc;

		DeserializationError error = deserializeJson(doc, json.c_str(), json.length());
		if (error) {
			xrstf::serialPrintf("Error: Failed to parse JSON: %s\n", error.c_str());
			return false;
		}

		// Only set this when fields _actually_ change, not only
		// if they are present in the server's response. Otherwise
		// a lazy server might force us to constantly update EEPROM.
		bool changes = false;

		if (doc.containsKey("sensorAddress")) {
			char sensorAddress = doc["sensorAddress"];
			if (sensorAddress != config->sensorAddress) {
				xrstf::serialPrintf("Update: Setting sensor address to 0x%x.\n", sensorAddress);
				config->sensorAddress = sensorAddress;
				changes               = true;
			}
		}

		if (doc.containsKey("sensorType")) {
			const char *sensorTypeStr = doc["sensorType"];

			char newSensorType = sensor::decodeTypeName(sensorTypeStr);
			if (newSensorType != config->sensorType) {
				xrstf::serialPrintf("Update: Setting sensor type to %s.\n", sensorTypeStr);
				config->sensorType = newSensorType;
				changes            = true;
			}
		}

		// if we changed anything related to the sensors, test the new settings
		// now and refuse to set invalid ones
		if (changes && config->sensorAddress != 0x0 && config->sensorType != 0x0) {
			if (!sensor::test(config->sensorAddress, config->sensorType)) {
				Serial.println("Failed to setup sensor with the new settings, refusing to use them.");
				return false;
			}
		}

		if (doc.containsKey("enableLED")) {
			bool enableLED = doc["enableLED"];
			if (enableLED != config->enableLED) {
				xrstf::serialPrintf("Update: %s LED.\n", enableLED ? "Enabling" : "Disabling");
				config->enableLED = enableLED;
				changes           = true;
			}
		}

		if (doc.containsKey("deviceName")) {
			const char *deviceName = doc["deviceName"];
			if (strcmp(deviceName, config->deviceName) != 0) {
				xrstf::serialPrintf("Update: Setting deviceName to '%s'.\n", deviceName);
				strncpy(config->deviceName, deviceName, sizeof(config->deviceName));
				changes = true;
			}
		}

		if (doc.containsKey("sleepMinutes")) {
			int sleepMinutes = doc["sleepMinutes"];
			if (sleepMinutes >= 0 && sleepMinutes <= 60 && ((char)sleepMinutes) != config->sleepMinutes) {
				xrstf::serialPrintf("Update: Setting sleep minutes to %d.\n", sleepMinutes);
				config->sleepMinutes = (char)sleepMinutes;
				changes              = true;
			}
		}

		if (doc.containsKey("pushURL")) {
			const char *pushURL = doc["pushURL"];
			if (strcmp(pushURL, config->pushURL) != 0) {
				xrstf::serialPrintf("Update: Setting pushURL to '%s'.\n", pushURL);
				strncpy(config->pushURL, pushURL, sizeof(config->pushURL));
				changes = true;
			}
		}

		if (doc.containsKey("pushFingerprint")) {
			char fingerprint[eeprom::FINGERPRINT_BYTES] = {0};

			const char *pushFingerprint = doc["pushFingerprint"];
			if (xrstf::normalizeFingerprint(pushFingerprint, eeprom::FINGERPRINT_BYTES, fingerprint)) {
				if (memcmp(config->pushFingerprint, fingerprint, eeprom::FINGERPRINT_BYTES) != 0) {
					Serial.println("Update: Updating push fingerprint.");
					memcpy(config->pushFingerprint, fingerprint, sizeof(config->pushFingerprint));
					changes = true;
				}
			}
		}

		if (doc.containsKey("ssid")) {
			const char *ssid = doc["ssid"];
			if (strcmp(ssid, config->ssid) != 0) {
				xrstf::serialPrintf("Update: Setting WiFi SSID to '%s'.\n", ssid);
				strncpy(config->ssid, ssid, sizeof(config->ssid));
				changes = true;
			}
		}

		if (doc.containsKey("password")) {
			const char *password = doc["password"];
			if (strcmp(password, config->password) != 0) {
				Serial.println("Update: Updated WiFi password.");
				strncpy(config->password, password, sizeof(config->password));
				changes = true;
			}
		}

		if (doc.containsKey("temperatureOffset")) {
			float temperatureOffset = doc["temperatureOffset"];
			if (temperatureOffset != config->temperatureOffset) {
				xrstf::serialPrintf("Update: Setting temperature offset to %s °C.\n", xrstf::fmtFloat(temperatureOffset));
				config->temperatureOffset = temperatureOffset;
				changes                   = true;
			}
		}

		if (doc.containsKey("humidityOffset")) {
			float humidityOffset = doc["humidityOffset"];
			if (humidityOffset != config->humidityOffset) {
				xrstf::serialPrintf("Update: Setting humidity offset to %s %%.\n", xrstf::fmtFloat(humidityOffset));
				config->humidityOffset = humidityOffset;
				changes                = true;
			}
		}

		if (doc.containsKey("pressureOffset")) {
			float pressureOffset = doc["pressureOffset"];
			if (pressureOffset != config->pressureOffset) {
				xrstf::serialPrintf("Update: Setting pressure offset to %s hPa.\n", xrstf::fmtFloat(pressureOffset));
				config->pressureOffset = pressureOffset;
				changes                = true;
			}
		}

		if (doc.containsKey("otaURL")) {
			const char *otaURL = doc["otaURL"];
			if (strcmp(otaURL, config->otaURL) != 0) {
				xrstf::serialPrintf("Update: Setting otaURL to '%s'.\n", otaURL);
				strncpy(config->otaURL, otaURL, sizeof(config->otaURL));
				changes = true;
			}
		}

		if (doc.containsKey("otaFingerprint")) {
			char fingerprint[eeprom::FINGERPRINT_BYTES] = {0};

			const char *otaFingerprint = doc["otaFingerprint"];
			if (xrstf::normalizeFingerprint(otaFingerprint, eeprom::FINGERPRINT_BYTES, fingerprint)) {
				if (memcmp(config->otaFingerprint, fingerprint, eeprom::FINGERPRINT_BYTES) != 0) {
					Serial.println("Update: Updating OTA fingerprint.");
					memcpy(config->otaFingerprint, fingerprint, sizeof(config->otaFingerprint));
					changes = true;
				}
			}
		}

		if (changes) {
			save(config);
		}

		// copy the OTA constraint out, so that the original request handling
		// can finish before beginning the OTA process.
		if (otaConstraintOut && strlen(config->otaURL) > 0 && doc.containsKey("otaConstraint")) {
			strncpy(otaConstraintOut, doc["otaConstraint"], 32);
		}

		return true;
	}

	bool hasFingerprint(const char fingerprint[FINGERPRINT_BYTES]) {
		for (size_t i = 0; i < FINGERPRINT_BYTES; ++i) {
			if (fingerprint[i]) {
				return true;
			}
		}

		return false;
	}
} // namespace eeprom
