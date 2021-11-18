#pragma once

#include "eeprom.h"
#include <LittleFS.h>

bool handlePushMode(eeprom::data *config);
bool pushFile(eeprom::data *config, const char* identifier, File *fs);
