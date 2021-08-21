#pragma once

#include "eeprom.h"
#include "sensor.h"

namespace multimeter {
	struct measurement {
		sensor::measurement sensor;
		uint8_t battery;
		uint16_t batteryRaw;
		uint32_t duration; // time in ms it took to perform the reading
	};

	void setup();
	void turnOn();
	void turnOff();
	void read(measurement *measurement, eeprom::data *config);
}
