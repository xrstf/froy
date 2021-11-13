#pragma once

#include "config.h"
#include <MCP7940NRTC.h>
#include <TimeLib.h>

namespace clock {
	extern MCP7940NRTC rtc;

	uint8_t encodeYear(uint8_t year);
	uint8_t decodeYear(uint8_t year);

	bool exists();
	bool isConfigured();
	bool read(tmElements_t &tm);
	bool set(tmElements_t &tm);
} // namespace clock
