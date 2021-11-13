#pragma once

#include <Arduino.h>

#define LOAD_EEPROM(var)                                                                                               \
	struct eeprom::data var;                                                                                           \
	eeprom::load(&var);

#define SAVE_EEPROM(var) eeprom::save(&var);

namespace eeprom {
	const char VERSION = 0x03;

	const int FINGERPRINT_BYTES = 20;

	// data the latest version of the data that is persisted in EEPROM
	struct data {
		char signature[4];
		char version;
		bool enableWebserver;
		bool enableWifi;
		bool enableLED;
		char sensorType;
		char sensorAddress; // usually 0x77 or 0x76 for BME280/680
		float temperatureOffset;
		float humidityOffset;
		float pressureOffset;
		char sleepMinutes;
		char deviceName[32];
		char pushURL[128];
		char pushFingerprint[FINGERPRINT_BYTES];
		char otaURL[128];
		char otaFingerprint[FINGERPRINT_BYTES];
		char ssid[64];
		char password[64];
		char seriesName[64];
		uint16_t maxSeriesPoints;
		uint16_t remainingSeriesPoints;
	};

	// version 2 data
	struct dataV2 {
		char signature[4];
		char version;
		bool enableWebserver;
		bool enableWifi;
		bool enableLED;
		char sensorType;
		char sensorAddress; // usually 0x77 or 0x76 for BME280/680
		float temperatureOffset;
		float humidityOffset;
		float pressureOffset;
		char sleepMinutes;
		char deviceName[32];
		char pushURL[128];
		char pushFingerprint[FINGERPRINT_BYTES];
		char otaURL[128];
		char otaFingerprint[FINGERPRINT_BYTES];
		char ssid[64];
		char password[64];
	};

	// version 1 data
	struct dataV1 {
		bool bootstrapDone;
		char version;
		bool enableWebserver;
		bool enableWifi;
		bool enableLED;
		char sensorType;
		char sensorAddress; // usually 0x77 or 0x76 for BME280/680
		char sleepMinutes;
		char pushURL[128];
		char ssid[64];
		char password[64];
		char deviceName[32];
		float temperatureOffset;
		float humidityOffset;
		float pressureOffset;
	};

	void init();
	void setDefaults(data *data);
	void load(data *data);
	void save(data *data);
	bool updateFromJSON(data *config, const String &json, char *otaConstraintOut);
	bool hasFingerprint(const char fingerprint[FINGERPRINT_BYTES]);
} // namespace eeprom
