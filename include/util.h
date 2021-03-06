#pragma once

#include "eeprom.h"
#include <Arduino.h>

extern bool pleaseRestart;

void scheduleRestart();
bool needsRestart();

void setupLED();
void setLED(bool enabled);
void enableLED();
void disableLED();
