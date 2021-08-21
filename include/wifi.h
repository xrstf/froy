#pragma once

#include <IPAddress.h>

namespace wifi {
	extern bool connected;
	extern IPAddress localIP;

	void connect();
	void disconnect();
}
