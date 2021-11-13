#pragma once

#include "eeprom.h"
#include <IPAddress.h>

namespace wifi {
	extern bool connected;
	extern IPAddress localIP;

	bool enabled(eeprom::data *config);
	void connect(eeprom::data *config);
	void disconnect();
} // namespace wifi
