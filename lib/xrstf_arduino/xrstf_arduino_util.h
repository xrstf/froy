#pragma once

#include <stdint.h>

namespace xrstf {
	void serialPrintf(const char *fmt, ...);

	void setupLED(uint8_t ledPin);
	void blinkLED(uint8_t ledPin, uint8_t times, uint32_t duration = 200, uint32_t cooldown = 500);
} // namespace xrstf
