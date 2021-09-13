#include "multimeter.h"
#include "config.h"
#include <Arduino.h>
#include <Wire.h>

namespace multimeter {
	void setupBattery() {
		pinMode(BATTERY_PIN, INPUT);
	}

	uint16_t readBattery() {
		return analogRead(BATTERY_PIN);
	}

	// calculatePercentage transforms the raw ADC value (0..1024) into a
	// percentage. The minimal value we ever received was 825 (aka 0%).
	uint8_t calculatePercentage(uint16_t raw) {
		// anything from [950..1024] is basically a brand new battery,
		// but the voltage will quickly drop and then hover around 950
		// for most of its lifetime before it starts to quickly drop;
		// for simplicity we consider anything above this "hover level"
		// as 100%.
		if (raw > 950) {
			return 100;
		}

		// in reality, this should never happen, as it's not enough
		// voltage to power the ESP8266 in the first place
		if (raw < 825) {
			return 0;
		}

		raw -= 825; // clamp [0..950] to [0..125] by ignoring the lowest
		            // values that can never be reached anyway

		return (uint8_t)(raw / 1.25);
	}

	void setupPowerTransistor() {
		pinMode(POWER_PIN, OUTPUT);
		turnOff();
	}

	void turnOn() {
		digitalWrite(POWER_PIN, HIGH);
	}

	void turnOff() {
		digitalWrite(POWER_PIN, LOW);
	}

	void setup() {
		setupBattery();
		setupPowerTransistor();
	}

	void read(measurement *m, eeprom::data *config) {
		if (!m || !config) {
			return;
		}

		turnOn();

		uint32_t start = millis();

		// read sensor data
		if (sensor::setup(config)) {
			sensor::read(&m->sensor, config);
		}

		// turn off ASAP, to save as many pico amps as possible ^^
		turnOff();

		// read battery
		m->batteryRaw = readBattery();
		m->battery    = calculatePercentage(m->batteryRaw);

		// finish up
		m->duration = millis() - start;
	}
} // namespace multimeter
