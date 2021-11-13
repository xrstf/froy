#include "util.h"
#include "config.h"
#include <xrstf_arduino_util.h>

bool pleaseRestart;

void scheduleRestart() {
	pleaseRestart = true;
}

bool needsRestart() {
	return pleaseRestart;
}

void setLED(bool enabled) {
	if (LED_PIN > 0) {
		digitalWrite(LED_PIN, enabled ? HIGH : LOW);
	}
}

void enableLED() {
	setLED(true);
}

void disableLED() {
	setLED(false);
}
