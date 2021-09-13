#pragma once

// informational purpose only
#define FROY_VERSION "4.2"

// set to 0 if there is no status LED on the board
#define LED_PIN 5

// A0 is the only pin on an ESP-WROOM-02 that has
// an ADC attached, all other pins are digital.
#define BATTERY_PIN A0

// this is the GPIO pin that controls the power to
// the sensor, I²C bus pull-ups and battery voltage divider
#define POWER_PIN 12

// Only some of the variants maintained in https://github.com/esp8266/Arduino/tree/master/variants
// have the correct pinout for an ESP-WROOM-02. To keep the code generic,
// we define our own constants. In the Arduino IDE, just choose "ESP8266 Generic".
#define I2C_SDA_PIN 2   // this is GPIO2, on physical pin 7
#define I2C_SCK_PIN 14  // this is GPIO14, on physical pin 3
