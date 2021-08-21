#include "xrstf_arduino_util.h"
#include <Arduino.h>
#include <stdlib.h>
#include <string.h>

namespace xrstf {
	// shared buffer for all serial printf's
	char __serial_buf[256];

	void serialPrintf(const char *fmt, ...) {
		va_list args;
		va_start(args, fmt);
		vsprintf(__serial_buf, fmt, args);
		va_end(args);

		Serial.print(__serial_buf);
	}

	void setupLED(uint8_t ledPin) {
		if (ledPin > 0) {
			pinMode(ledPin, OUTPUT);
			digitalWrite(ledPin, LOW);
		}
	}

	void blinkLED(uint8_t ledPin, uint8_t times, uint32_t duration, uint32_t cooldown) {
		if (ledPin > 0) {
			for (uint8_t i = 0; i < times; i++) {
				digitalWrite(ledPin, HIGH);
				delay(duration);
				digitalWrite(ledPin, LOW);
				delay(duration);
			}

			delay(cooldown);
		}
	}
} // namespace xrstf
