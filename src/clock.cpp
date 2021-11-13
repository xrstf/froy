#include "clock.h"

namespace clock {
	MCP7940NRTC rtc(I2C_SDA_PIN, I2C_SCK_PIN);

	uint8_t encodeYear(uint8_t year) {
		return CalendarYrToTm(year);
	}

	uint8_t decodeYear(uint8_t year) {
		return tmYearToCalendar(year);
	}

	bool exists() {
		return rtc.chipPresent();
	}

	bool isConfigured() {
		tmElements_t tm;
		return rtc.read(tm);
	}

	bool read(tmElements_t &tm) {
		return rtc.read(tm);
	}

	bool set(tmElements_t &tm) {
		return rtc.write(tm);
	}
} // namespace clock
