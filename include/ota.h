#pragma once

#include <Arduino.h>

namespace ota {
	void update(String &endpointURL, String &constraint, char fingerprint[20]);
}
