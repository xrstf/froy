#pragma once

// informational purpose only
#define FROY_VERSION "4.1"

// set to 0 if there is no status LED on the board
#define LED_PIN 5

#define BATTERY_PIN A0
// #define BATTERY_PIN 0

// if this is defined, it's the GPIO pin that controls
// the power to the sensor and I²C bus pull-ups;
// set it via platformio.ini environments
// #define SENSOR_POWER_PIN 12

// Only some of the variants maintained in https://github.com/esp8266/Arduino/tree/master/variants
// have the correct pinout for an ESP-WROOM-02. To keep the code generic,
// we define our own constants. In the Arduino IDE, just choose "ESP8266 Generic".
#define I2C_SDA_PIN 2   // this is GPIO2, on physical pin 7
#define I2C_SCK_PIN 14  // this is GPIO14, on physical pin 3
