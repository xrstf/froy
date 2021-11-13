#include "rtc.h"
#include <xrstf_arduino_util.h>

namespace rtc {
	MCP7940NRTC rtc(I2C_SDA_PIN, I2C_SCK_PIN);

	uint8_t encodeYear(uint16_t year) {
		return CalendarYrToTm(year);
	}

	uint16_t decodeYear(uint8_t year) {
		return tmYearToCalendar(year);
	}

	bool exists() {
		isConfigured(); // need to run read() once to init the _exists flag in the library

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
		printToSerial(tm);
		return rtc.write(tm);
	}

	void printToSerial(tmElements_t &tm) {
		xrstf::serialPrintf("Time & Date: %04d-%02d-%02d %02d:%02d:%02d\n", decodeYear(tm.Year), tm.Month, tm.Day, tm.Hour, tm.Minute, tm.Second);
	}
} // namespace rtc
