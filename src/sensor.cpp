#include "sensor.h"
#include "config.h"
#include <Wire.h>

namespace sensor {
	// Use BME via I2C, so do not give any further arguments.
	Adafruit_BME280 bme280;
	Adafruit_BME680 bme680(&Wire);
	Adafruit_BMP280 bmp280(&Wire);

	const char *typeName(char type) {
		switch (type) {
		case TYPE_BME280:
			return "bme280";
		case TYPE_BME680:
			return "bme680";
		case TYPE_BMP280:
			return "bmp280";
		default:
			return "undefined";
		}
	}

	char decodeTypeName(const char *typeName) {
		if (strcmp(typeName, sensor::typeName(sensor::TYPE_BME280)) == 0) {
			return sensor::TYPE_BME280;
		}

		if (strcmp(typeName, sensor::typeName(sensor::TYPE_BME680)) == 0) {
			return sensor::TYPE_BME680;
		}

		if (strcmp(typeName, sensor::typeName(sensor::TYPE_BMP280)) == 0) {
			return sensor::TYPE_BMP280;
		}

		return 0x0;
	}

	bool test(char address, char type) {
		if (address == 0) {
			return false;
		}

		// manually set up the I2C bus, as we need to
		// override the pin-out to match an ESP-WROOM-02
		Wire.begin(I2C_SDA_PIN, I2C_SCK_PIN);

		switch (type) {
		case TYPE_BME280: {
			if (!bme280.begin(address, &Wire)) {
				return false;
			}

			Adafruit_BME280::sensor_mode operatingMode            = Adafruit_BME280::MODE_FORCED;
			Adafruit_BME280::sensor_sampling tempOversampling     = Adafruit_BME280::SAMPLING_X8;
			Adafruit_BME280::sensor_sampling humidityOversampling = Adafruit_BME280::SAMPLING_X2;
			Adafruit_BME280::sensor_sampling pressureOversampling = Adafruit_BME280::SAMPLING_X4;
			Adafruit_BME280::sensor_filter filtering              = Adafruit_BME280::FILTER_X2;
			Adafruit_BME280::standby_duration standbyTime         = Adafruit_BME280::STANDBY_MS_500;

			bme280.setSampling(operatingMode, tempOversampling, pressureOversampling, humidityOversampling, filtering, standbyTime);
			return true;
		}

		case TYPE_BME680:
			if (!bme680.begin(address)) {
				return false;
			}

			// Set up oversampling and filter initialization
			bme680.setTemperatureOversampling(BME680_OS_8X);
			bme680.setHumidityOversampling(BME680_OS_2X);
			bme680.setPressureOversampling(BME680_OS_4X);
			bme680.setIIRFilterSize(BME680_FILTER_SIZE_3);
			bme680.setGasHeater(320, 150); // 320*C for 150 ms
			return true;

		case TYPE_BMP280: {
			if (!bmp280.begin(address)) {
				return false;
			}

			Adafruit_BMP280::sensor_mode operatingMode            = Adafruit_BMP280::MODE_FORCED;
			Adafruit_BMP280::sensor_sampling tempOversampling     = Adafruit_BMP280::SAMPLING_X8;
			Adafruit_BMP280::sensor_sampling pressureOversampling = Adafruit_BMP280::SAMPLING_X4;
			Adafruit_BMP280::sensor_filter filtering              = Adafruit_BMP280::FILTER_X2;
			Adafruit_BMP280::standby_duration standbyTime         = Adafruit_BMP280::STANDBY_MS_500;

			bmp280.setSampling(operatingMode, tempOversampling, pressureOversampling, filtering, standbyTime);
			return true;
		}

		default:
			return false;
		}
	}

	bool setup(eeprom::data *config) {
		return test(config->sensorAddress, config->sensorType);
	}

	bool read(measurement *m, eeprom::data *config) {
		if (config->sensorType != TYPE_BME280 && config->sensorType != TYPE_BME680 && config->sensorType != TYPE_BMP280) {
			return false;
		}

		m->temperature        = NAN;
		m->humidity           = NAN;
		m->pressure           = NAN;
		m->temperatureRetries = 0;
		m->humidityRetries    = 0;
		m->pressureRetries    = 0;

		char maxRetries = 10;

		// read temperature
		for (char i = 0; i < maxRetries; ++i) {
			switch (config->sensorType) {
			case TYPE_BME280:
				m->temperature = bme280.readTemperature();
				break;
			case TYPE_BME680:
				m->temperature = bme680.readTemperature();
				break;
			case TYPE_BMP280:
				m->temperature = bmp280.readTemperature();
				break;
			}

			if (!isnan(m->temperature)) {
				m->temperature += config->temperatureOffset;
				break;
			}

			m->temperatureRetries++;
			delay(20);
		}

		// read pressure
		for (char i = 0; i < maxRetries; ++i) {
			switch (config->sensorType) {
			case TYPE_BME280:
				m->pressure = bme280.readPressure() / 100.0F;
				break;
			case TYPE_BME680:
				m->pressure = bme680.readPressure() / 100.0F;
				break;
			case TYPE_BMP280:
				m->pressure = bmp280.readPressure() / 100.0F;
				break;
			}

			if (!isnan(m->pressure)) {
				m->pressure += config->pressureOffset;
				break;
			}

			m->pressureRetries++;
			delay(20);
		}

		// read humidity
		if (config->sensorType != TYPE_BMP280) {
			for (char i = 0; i < maxRetries; ++i) {
				switch (config->sensorType) {
				case TYPE_BME280:
					m->humidity = bme280.readHumidity();
					break;
				case TYPE_BME680:
					m->humidity = bme680.readHumidity();
					break;
				}

				if (!isnan(m->humidity)) {
					m->humidity += config->humidityOffset;
					break;
				}

				m->humidityRetries++;
				delay(20);
			}
		}

		return true;
	}
} // namespace sensor
