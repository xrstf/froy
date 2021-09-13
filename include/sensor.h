#pragma once

#include "eeprom.h"
#include <Adafruit_BME280.h>
#include <Adafruit_BME680.h>
#include <Adafruit_BMP280.h>

namespace sensor {
	const char TYPE_BME280 = 0x01;
	const char TYPE_BME680 = 0x02;
	const char TYPE_BMP280 = 0x03;

	extern Adafruit_BME280 bme280;
	extern Adafruit_BME680 bme680;
	extern Adafruit_BMP280 bmp280;

	struct measurement {
		float temperature;
		float pressure;
		float humidity;
		uint8_t temperatureRetries;
		uint8_t pressureRetries;
		uint8_t humidityRetries;
	};

	const char *typeName(char type);
	char decodeTypeName(const char *typeName);

	bool setup(eeprom::data *config);
	bool read(measurement *m, eeprom::data *config);
	bool test(char address, char sensorType);
} // namespace sensor
