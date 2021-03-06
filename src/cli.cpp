#include "cli.h"
#include "config.h"
#include "eeprom.h"
#include "multimeter.h"
#include "ota.h"
#include "rtc.h"
#include "sensor.h"
#include "util.h"
#include "webserver.h"
#include "datalogger.h"
#include "wifi.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <NTPClient.h>
#include <TimeLib.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <xrstf_arduino_util.h>
#include <xrstf_util.h>

namespace cli {
	void setup() {
		Serial.begin(115200);
		Serial.println(""); // ensure a newline after the ESP8266 boot garbage output
		Serial.println("Froy says Moin!");
	}

	void toggleWebserver(bool flag) {
		LOAD_EEPROM(data);
		data.enableWebserver = flag;
		SAVE_EEPROM(data);
	}

	void handleEnableWebserverCommand() {
		toggleWebserver(true);
		Serial.println("OK: Successfully enabled webserver.");
		webserver::start();
	}

	void handleDisableWebserverCommand() {
		toggleWebserver(false);
		Serial.println("OK: Successfully disabled webserver.");
		webserver::stop();
	}

	void toggleLED(bool flag) {
		LOAD_EEPROM(data);
		data.enableLED = flag;
		SAVE_EEPROM(data);
	}

	void handleEnableLEDCommand() {
		toggleLED(true);
		Serial.println("OK: Successfully enabled LED.");
	}

	void handleDisableLEDCommand() {
		toggleLED(false);
		Serial.println("OK: Successfully disabled LED.");
	}

	void toggleWifi(bool flag) {
		LOAD_EEPROM(data);
		data.enableWifi = flag;
		SAVE_EEPROM(data);
	}

	void handleEnableWifiCommand() {
		toggleWifi(true);
		Serial.println("OK: Successfully enabled WiFi.");
		LOAD_EEPROM(config);
		wifi::connect(&config);
	}

	void handleDisableWifiCommand() {
		toggleWifi(false);
		Serial.println("OK: Successfully disabled WiFi.");
		wifi::disconnect();
	}

	void handleSetSensorTypeCommand(char *cmdArgs) {
		LOAD_EEPROM(data);

		data.sensorType = sensor::decodeTypeName(cmdArgs);
		if (data.sensorType == 0x0) {
			xrstf::serialPrintf("Error: unknown sensor type, known types are: %s, %s, %s", sensor::typeName(sensor::TYPE_BME280), sensor::typeName(sensor::TYPE_BME680), sensor::typeName(sensor::TYPE_BMP280));
			return;
		}

		if (data.sensorAddress != 0) {
			if (!sensor::test(data.sensorAddress, data.sensorType)) {
				// This is just a warning, otherwise it would be impossible to switch from
				// BME280 @ 0x76 to BME680 @ 0x77.
				xrstf::serialPrintf("Warning: This sensor type does not respond at address 0x%x.\n", data.sensorAddress);
			}
		}

		SAVE_EEPROM(data);
		xrstf::serialPrintf("OK: Successfully set sensor type to %s.", sensor::typeName(data.sensorType));
	}

	void handleSetSensorAddressCommand(char *cmdArgs) {
		LOAD_EEPROM(data);

		if (data.sensorType == 0) {
			Serial.println("Error: set the sensor type first with set-sensor-type [bme280|bme680|bmp280]");
			return;
		}

		if (strlen(cmdArgs) != 2) {
			Serial.println("Error: address must be 2 hex digits (e.g. 77).");
			return;
		}

		char address = 0x00;
		if (xrstf::hexdecode(&address, 1, cmdArgs) != 2) {
			Serial.println("Error: invalid hex-encoding for address.");
			return;
		}

		if (!sensor::test(address, data.sensorType)) {
			xrstf::serialPrintf("Error: No I2C device responds to address 0x%x.\n", address);
			return;
		}

		data.sensorAddress = address;
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: Successfully configured %s at address 0x%x.\n", sensor::typeName(data.sensorType), address);
	}

	void handleScanForSensorCommand() {
		LOAD_EEPROM(data);

		xrstf::serialPrintf("Scanning for I??C %s sensors...\n", sensor::typeName(data.sensorType));

		for (uint8_t address = 0; address <= 127; ++address) {
			if (sensor::test(address, data.sensorType)) {
				xrstf::serialPrintf("Found sensor at 0x%x.\n", address);
			}
		}

		Serial.println("Scan completed.");
	}

	bool parseCalibrationOffset(char *input, float *target, const char *unit) {
		if (strlen(input) == 0) {
			Serial.println("Error: A number must be provided.");
			return false;
		}

		*target = strtof(input, NULL);

		if (*target < -100) {
			xrstf::serialPrintf("Error: Offset cannot be smaller than -100%s.", unit);
			return false;
		}

		if (*target > 100) {
			xrstf::serialPrintf("Error: Offset cannot be greater than 100%s.", unit);
			return false;
		}

		return true;
	}

	void handleSetTemperatureOffsetCommand(char *flags) {
		LOAD_EEPROM(data);

		float offset;
		if (!parseCalibrationOffset(flags, &offset, "??C")) {
			return;
		}

		data.temperatureOffset = offset;
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: Temperature offset set to %s??C.\n", xrstf::fmtFloat(offset));
	}

	void handleSetHumidityOffsetCommand(char *flags) {
		LOAD_EEPROM(data);

		float offset;
		if (!parseCalibrationOffset(flags, &offset, "%")) {
			return;
		}

		data.humidityOffset = offset;
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: Humidity offset set to %s%%.\n", xrstf::fmtFloat(offset));
	}

	void handleSetPressureOffsetCommand(char *flags) {
		LOAD_EEPROM(data);

		float offset;
		if (!parseCalibrationOffset(flags, &offset, "hPa")) {
			return;
		}

		data.pressureOffset = offset;
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: Pressure offset set to %shPa.\n", xrstf::fmtFloat(offset));
	}

	void handleMeasureCommand() {
		LOAD_EEPROM(config);

		if (config.sensorType == 0x0) {
			Serial.println("Error: No sensor type configured yet, use 'set-sensor-type'.");
			return;
		}

		if (config.sensorAddress == 0x0) {
			Serial.println("Error: No sensor address configured yet, use 'set-sensor-address XX'.");
			return;
		}

		multimeter::measurement m;
		multimeter::read(&m, &config);

		xrstf::serialPrintf("Temperature: %s ??C (%d retries)\n", xrstf::fmtFloat(m.sensor.temperature), m.sensor.temperatureRetries);
		xrstf::serialPrintf("Humidity...: %s %% (%d retries)\n", xrstf::fmtFloat(m.sensor.humidity), m.sensor.humidityRetries);
		xrstf::serialPrintf("Pressure...: %s hPa (%d retries)\n", xrstf::fmtFloat(m.sensor.pressure), m.sensor.pressureRetries);
		xrstf::serialPrintf("Battery....: %d units\n", m.battery);
		xrstf::serialPrintf("Duration...: %d ms\n", m.duration);
	}

	void handleSetDeviceNameCommand(char *flags) {
		if (strlen(flags) == 0) {
			Serial.println("Error: Device name must not be empty.");
			return;
		}

		if (strlen(flags) > 31) {
			Serial.println("Error: Device name must be less than 32 characters.");
			return;
		}

		LOAD_EEPROM(data);
		strncpy(data.deviceName, flags, sizeof(data.deviceName));
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: Device name successfully updated to '%s'.\n", flags);
	}

	void handleSetWifiSSIDCommand(char *flags) {
		if (strlen(flags) == 0) {
			Serial.println("Error: SSID must not be empty.");
			return;
		}

		LOAD_EEPROM(data);
		strncpy(data.ssid, flags, sizeof(data.ssid));
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: SSID successfully updated to '%s'.\n", flags);
	}

	void handleSetWifiPasswordCommand(char *flags) {
		LOAD_EEPROM(data);
		strncpy(data.password, flags, sizeof(data.password));
		SAVE_EEPROM(data);

		Serial.println("OK: Password successfully updated.");
	}

	void handleSetPushURLCommand(char *flags) {
		if (strlen(flags) == 0) {
			Serial.println("Error: URL must not be empty.");
			return;
		}

		if (strlen(flags) > 127) {
			Serial.println("Error: URL must not exceed 127 characters.");
			return;
		}

		LOAD_EEPROM(data);
		strncpy(data.pushURL, flags, sizeof(data.pushURL));
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: Push URL successfully updated to '%s'.\n", flags);

		if (data.sleepMinutes == 0) {
			Serial.println("Hint: Remember to enable push mode by setting sleep minutes to a positive value.");
		}
	}

	void handleSetOTAURLCommand(char *flags) {
		if (strlen(flags) == 0) {
			Serial.println("Error: URL must not be empty.");
			return;
		}

		if (strlen(flags) > 127) {
			Serial.println("Error: URL must not exceed 127 characters.");
			return;
		}

		LOAD_EEPROM(data);
		strncpy(data.otaURL, flags, sizeof(data.otaURL));
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: OTA URL successfully updated to '%s'.\n", flags);
	}

	bool setFingerprint(char *flags, char *target) {
		if (strlen(flags) == 0) {
			Serial.println("Error: Fingerprint must not be empty.");
			return false;
		}

		char fingerprint[eeprom::FINGERPRINT_BYTES] = {0};

		if (strlen(flags) >= eeprom::FINGERPRINT_BYTES * 2) {
			if (!xrstf::normalizeFingerprint(flags, eeprom::FINGERPRINT_BYTES, fingerprint)) {
				Serial.println("Error: Fingerprint must be a 40 digit hex string.");
				return false;
			}
		}

		if (eeprom::hasFingerprint(fingerprint)) {
			memcpy(target, fingerprint, eeprom::FINGERPRINT_BYTES);

			char buf[41] = {0};
			xrstf::hexencode(fingerprint, eeprom::FINGERPRINT_BYTES, buf);
			xrstf::serialPrintf("OK: Fingerprint successfully updated to '%s'.\n", buf);
		} else {
			memset(target, 0x0, eeprom::FINGERPRINT_BYTES);
			Serial.println("OK: Fingerprint successfully removed.");
		}

		return true;
	}

	void handleSetOTAFingerprintCommand(char *flags) {
		LOAD_EEPROM(data);

		if (setFingerprint(flags, data.otaFingerprint)) {
			SAVE_EEPROM(data);
		}
	}

	void handleSetPushFingerprintCommand(char *flags) {
		LOAD_EEPROM(data);

		if (setFingerprint(flags, data.pushFingerprint)) {
			SAVE_EEPROM(data);
		}
	}

	void handleSetSleepMinutesCommand(char *flags) {
		LOAD_EEPROM(data);

		if (strlen(data.pushURL) == 0 && strlen(data.seriesName) == 0) {
			Serial.println("Error: A push URL or time series name must be configured first.");
			return;
		}

		if (strlen(flags) == 0) {
			Serial.println("Error: A number must be provided.");
			return;
		}

		if (strlen(flags) > 3) {
			Serial.println("Error: Number of minutes must be at most 3 digits long.");
			return;
		}

		int minutesInt = 0;
		if (!xrstf::safeStringToInt(flags, &minutesInt)) {
			Serial.println("Error: Invalid number given.");
			return;
		}

		if (minutesInt < 0) {
			Serial.println("Error: Number cannot be negative; use 0 to disable sleep mode.");
			return;
		}

		if (minutesInt > 60) {
			Serial.println("Error: Cannot sleep for more than 60 minutes.");
			return;
		}

		data.sleepMinutes = (char)minutesInt;
		SAVE_EEPROM(data);

		if (minutesInt == 0) {
			Serial.println("OK: Running in stand-by mode now.");
		} else if (strlen(data.seriesName) > 0) {
			xrstf::serialPrintf("OK: Data logging mode enabled, going to sleep for %d minutes between samples.\n", data.sleepMinutes);
		} else {
			xrstf::serialPrintf("OK: Push mode enabled, going to sleep for %d minutes between pushes.\n", data.sleepMinutes);
		}
	}

	void handleSetTimeSeriesCommand(char *flags) {
		LOAD_EEPROM(data);

		if (strlen(flags) == 0) {
			Serial.println("Error: The time series name may not be empty.");
			return;
		}

		if (strlen(flags) > 32) {
			Serial.println("Error: Time series name must be at most 32 characters.");
			return;
		}

		strncpy(data.seriesName, flags, sizeof(data.seriesName));
		data.pointsSampled = 0;
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: Going to log data as %s time series.\n", data.seriesName);
	}

	void handleDisableTimeSeriesCommand() {
		LOAD_EEPROM(data);
		memset(data.seriesName, 0x0, sizeof(data.seriesName));
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: Time series mode disabled.\n");
	}

	void handleSetTimeSeriesPointsCommand(char *flags) {
		LOAD_EEPROM(data);

		if (strlen(flags) == 0) {
			Serial.println("Error: A number must be provided.");
			return;
		}

		if (strlen(flags) > 5) {
			Serial.println("Error: Number of data points must be at most 5 digits long.");
			return;
		}

		int pointsInt = 0;
		if (!xrstf::safeStringToInt(flags, &pointsInt)) {
			Serial.println("Error: Invalid number given.");
			return;
		}

		if (pointsInt < 0) {
			Serial.println("Error: Number cannot be negative; use 0 to log data indefinitely.");
			return;
		}

		if (pointsInt > 16000) {
			Serial.println("Error: Limit must be below 16k.");
			return;
		}

		data.maxSeriesPoints = (uint16_t)pointsInt;
		data.pointsSampled   = 0;
		SAVE_EEPROM(data);

		if (pointsInt == 0) {
			Serial.println("OK: Limit removed, logging data indefinitely now.");
		} else {
			xrstf::serialPrintf("OK: Going to log at most %d points before sleeping indefinitely.\n", data.maxSeriesPoints);
		}
	}

	void handleWipeCommand() {
		LOAD_EEPROM(data);
		eeprom::setDefaults(&data);
		SAVE_EEPROM(data);

		Serial.println("OK: All settings reset to factory defaults.");
	}

	void handleShowConfigurationCommand() {
		LOAD_EEPROM(data);

		xrstf::serialPrintf("Software version..: %s\n", FROY_VERSION);
		xrstf::serialPrintf("EEPROM version....: %d\n", data.version);
		xrstf::serialPrintf("Device name.......: '%s'\n", data.deviceName);
		xrstf::serialPrintf("Sensor address....: 0x%x\n", data.sensorAddress);
		xrstf::serialPrintf("Sensor type.......: %s\n", sensor::typeName(data.sensorType));
		xrstf::serialPrintf("Temperature offset: %s ??C\n", xrstf::fmtFloat(data.temperatureOffset));
		xrstf::serialPrintf("Humidity offset...: %s %%\n", xrstf::fmtFloat(data.humidityOffset));
		xrstf::serialPrintf("Pressure offset...: %s hPa\n", xrstf::fmtFloat(data.pressureOffset));
		xrstf::serialPrintf("LED enabled.......: %s\n", data.enableLED ? "yes" : "no");
		xrstf::serialPrintf("Webserver enabled.: %s\n", data.enableWebserver ? "yes" : "no");
		xrstf::serialPrintf("WiFi enabled......: %s\n", data.enableWifi ? "yes" : "no");

		if (data.sleepMinutes == 0) {
			Serial.println("Push enabled......: no");
		} else if (strlen(data.pushURL) > 0 && strlen(data.seriesName) == 0) {
			xrstf::serialPrintf("Push enabled......: yes (every %d minute(s))\n", data.sleepMinutes);
		}

		if (strlen(data.seriesName) == 0) {
			Serial.println("Data Logging......: no");
		} else {
			if (data.sleepMinutes == 0) {
				Serial.println("Data Logging......: no");
			} else {
				xrstf::serialPrintf("Data Logging......: yes (every %d minute(s))\n", data.sleepMinutes);
				xrstf::serialPrintf("Startup Delay.....: %d ms\n", data.startupDelay);
			}
			xrstf::serialPrintf("Time Series.......: %s\n", data.seriesName);

			if (data.maxSeriesPoints > 0) {
				xrstf::serialPrintf("Max Data Points...: %d\n", data.maxSeriesPoints);
			} else {
				xrstf::serialPrintf("Max Data Points...: (unlimited)\n");
			}

			if (data.batchUploadSize > 0) {
				xrstf::serialPrintf("Batch Upload......: after %d samples\n", data.batchUploadSize);
			} else {
				xrstf::serialPrintf("Batch Upload......: (disabled)\n");
			}
		}

		char buf[41] = {0};

		if (eeprom::hasFingerprint(data.pushFingerprint)) {
			xrstf::hexencode(data.pushFingerprint, eeprom::FINGERPRINT_BYTES, buf);
		} else {
			strncpy(buf, "(none)", sizeof(data.pushFingerprint));
		}

		xrstf::serialPrintf("Push URL..........: %s\n", data.pushURL);
		xrstf::serialPrintf("Push Fingerprint..: %s\n", buf);

		if (eeprom::hasFingerprint(data.otaFingerprint)) {
			xrstf::hexencode(data.otaFingerprint, eeprom::FINGERPRINT_BYTES, buf);
		} else {
			strncpy(buf, "(none)", sizeof(data.otaFingerprint));
		}

		xrstf::serialPrintf("OTA URL...........: %s\n", data.otaURL);
		xrstf::serialPrintf("OTA Fingerprint...: %s\n", buf);

		char *asterisks = (char *)malloc(strlen(data.password) + 1);
		memset(asterisks, 0, strlen(data.password) + 1);
		memset(asterisks, '*', strlen(data.password));

		xrstf::serialPrintf("WiFi SSID.........: '%s'\n", data.ssid);
		xrstf::serialPrintf("WiFi password.....: '%s'\n", asterisks);

		if (wifi::connected) {
			xrstf::serialPrintf("Current IP........: %s\n", wifi::localIP.toString().c_str());
		}

		delete asterisks;
	}

	void handleLocalIPCommand() {
		if (wifi::connected) {
			xrstf::serialPrintf("My IP is %s.\n", wifi::localIP.toString().c_str());
		} else {
			Serial.println("Not connected.");
		}
	}

	void handleBatteryCommand() {
		LOAD_EEPROM(data);

		// disable sensor reading
		data.sensorType = 0x0;

		multimeter::measurement m;
		multimeter::read(&m, &data);

		xrstf::serialPrintf("Battery level is %d units.\n", m.battery);
	}

	void handleRestartCommand() {
		Serial.println("Restarting now...");
		scheduleRestart();
	}

	void handleOTACommand(char *flags) {
		LOAD_EEPROM(data);

		if (strlen(data.otaURL) == 0) {
			Serial.println("Error: No OTA URL configured.");
			return;
		}

		String url(data.otaURL);
		String constraint("latest");

		if (flags && strlen(flags) > 0) {
			constraint = flags;
		}

		ota::update(url, constraint, data.otaFingerprint);
	}

	void handleGetNTPTimeCommand() {
		if (!wifi::connected) {
			Serial.println("Error: Must be connected to WiFi.");
			return;
		}

		// setup NTP client
		WiFiUDP ntpUDP;
		NTPClient timeClient(ntpUDP);

		// fetch current UNIX timestamp
		timeClient.begin();
		if (timeClient.update()) {
			time_t epoch = timeClient.getEpochTime();

			tmElements_t tm;
			breakTime(epoch, tm);

			rtc::printToSerial(tm);
		}
		timeClient.end();
	}

	void handleShowTimeSeriesCommand(char *flags) {
		if (!flags || strlen(flags) == 0) {
			LOAD_EEPROM(data);
			if (strlen(data.seriesName) == 0) {
				Serial.println("Error: No time series name configured or given in command.");
				return;
			}

			flags = data.seriesName;
		}

		Datalogger dl(LittleFS, "m");
		if (!dl.begin()) {
			Serial.println("Failed to init LittleFS.");
			return;
		}

		dl.printMetric(flags);
		dl.end();
	}

	void handleClearTimeSeriesCommand(char *flags) {
		if (!flags || strlen(flags) == 0) {
			LOAD_EEPROM(data);
			if (strlen(data.seriesName) == 0) {
				Serial.println("Error: No time series name configured or given in command.");
				return;
			}

			flags = data.seriesName;
		}

		Datalogger dl(LittleFS, "m");
		if (!dl.begin()) {
			Serial.println("Failed to init LittleFS.");
			return;
		}

		dl.removeMetric(flags);
		dl.end();

		xrstf::serialPrintf("OK: Time series %s removed.\n", flags);
	}

	void handleClearAllTimeSeriesCommand() {
		Datalogger dl(LittleFS, "m");
		if (!dl.begin()) {
			Serial.println("Failed to init LittleFS.");
			return;
		}

		dl.wipe();
		dl.end();

		Serial.println("OK: All time series were removed.");
	}

	void handleSetBatchSizeCommand(char *flags) {
		LOAD_EEPROM(data);

		if (strlen(data.seriesName) == 0) {
			Serial.println("Error: A time series name must be configured first.");
			return;
		}

		if (strlen(flags) == 0) {
			Serial.println("Error: A number must be provided.");
			return;
		}

		if (strlen(flags) > 5) {
			Serial.println("Error: Number of data points must be at most 5 digits long.");
			return;
		}

		int batchInt = 0;
		if (!xrstf::safeStringToInt(flags, &batchInt)) {
			Serial.println("Error: Invalid number given.");
			return;
		}

		if (batchInt < 0) {
			Serial.println("Error: Number cannot be negative; use 0 to disable batch uploads.");
			return;
		}

		if (batchInt > 16000) {
			Serial.println("Error: Batch size cannot be larger than 16k.");
			return;
		}

		data.batchUploadSize = (uint16_t)batchInt;
		SAVE_EEPROM(data);

		if (batchInt == 0) {
			Serial.println("OK: Data logging only now, not performing batch uploads.");
		} else {
			xrstf::serialPrintf("OK: Will try to upload after every %d samples.\n", data.batchUploadSize);
		}
	}

	void handleSetStartupDelayCommand(char *flags) {
		LOAD_EEPROM(data);

		if (strlen(flags) == 0) {
			Serial.println("Error: A number must be provided.");
			return;
		}

		if (strlen(flags) > 5) {
			Serial.println("Error: Startup delay must be at most 5 digits long.");
			return;
		}

		int delayInt = 0;
		if (!xrstf::safeStringToInt(flags, &delayInt)) {
			Serial.println("Error: Invalid number given.");
			return;
		}

		if (delayInt < 0) {
			Serial.println("Error: Number cannot be negative.");
			return;
		}

		if (delayInt > 16000) {
			Serial.println("Error: Startup delay cannot be larger than 16 seconds.");
			return;
		}

		data.startupDelay = (uint16_t)delayInt;
		SAVE_EEPROM(data);

		xrstf::serialPrintf("OK: Will sleep %d milliseconds on startup.\n", data.startupDelay);
	}

	void clear() {
		while (Serial.available() > 0) {
			Serial.read();
		}
	}

	void handleCommand() {
		if (Serial.available() > 0) {
			char commandStr[128];
			Serial.readBytesUntil('\n', commandStr, 127);

			// trim trailing newlines, thanks to https://stackoverflow.com/a/28462221
			commandStr[strcspn(commandStr, "\r\n")] = 0;

			if (xrstf::startsWith(commandStr, "set-wifi-ssid ")) {
				handleSetWifiSSIDCommand(commandStr + strlen("set-wifi-ssid "));
			} else if (xrstf::startsWith(commandStr, "set-wifi-password ")) {
				handleSetWifiPasswordCommand(commandStr + strlen("set-wifi-password "));
			} else if (xrstf::startsWith(commandStr, "set-device-name ")) {
				handleSetDeviceNameCommand(commandStr + strlen("set-device-name "));
			} else if (xrstf::startsWith(commandStr, "set-sensor-type ")) {
				handleSetSensorTypeCommand(commandStr + strlen("set-sensor-type "));
			} else if (xrstf::startsWith(commandStr, "set-sensor-address ")) {
				handleSetSensorAddressCommand(commandStr + strlen("set-sensor-address "));
			} else if (xrstf::startsWith(commandStr, "scan-for-sensors")) {
				handleScanForSensorCommand();
			} else if (xrstf::startsWith(commandStr, "set-push-url ")) {
				handleSetPushURLCommand(commandStr + strlen("set-push-url "));
			} else if (xrstf::startsWith(commandStr, "set-push-fingerprint ")) {
				handleSetPushFingerprintCommand(commandStr + strlen("set-push-fingerprint "));
			} else if (xrstf::startsWith(commandStr, "set-ota-url ")) {
				handleSetOTAURLCommand(commandStr + strlen("set-ota-url "));
			} else if (xrstf::startsWith(commandStr, "set-ota-fingerprint ")) {
				handleSetOTAFingerprintCommand(commandStr + strlen("set-ota-fingerprint "));
			} else if (xrstf::startsWith(commandStr, "set-sleep-minutes ")) {
				handleSetSleepMinutesCommand(commandStr + strlen("set-sleep-minutes "));
			} else if (xrstf::startsWith(commandStr, "set-temperature-offset ")) {
				handleSetTemperatureOffsetCommand(commandStr + strlen("set-temperature-offset "));
			} else if (xrstf::startsWith(commandStr, "set-humidity-offset ")) {
				handleSetHumidityOffsetCommand(commandStr + strlen("set-humidity-offset "));
			} else if (xrstf::startsWith(commandStr, "set-pressure-offset ")) {
				handleSetPressureOffsetCommand(commandStr + strlen("set-pressure-offset "));
			} else if (xrstf::startsWith(commandStr, "set-startup-delay ")) {
				handleSetStartupDelayCommand(commandStr + strlen("set-startup-delay "));
			} else if (xrstf::startsWith(commandStr, "set-timeseries ")) {
				handleSetTimeSeriesCommand(commandStr + strlen("set-timeseries "));
			} else if (xrstf::startsWith(commandStr, "set-time-series ")) {
				handleSetTimeSeriesCommand(commandStr + strlen("set-time-series "));
			} else if (xrstf::startsWith(commandStr, "show-timeseries ")) {
				handleShowTimeSeriesCommand(commandStr + strlen("show-timeseries "));
			} else if (xrstf::startsWith(commandStr, "show-time-series ")) {
				handleShowTimeSeriesCommand(commandStr + strlen("show-time-series "));
			} else if (xrstf::startsWith(commandStr, "clear-timeseries ")) {
				handleClearTimeSeriesCommand(commandStr + strlen("clear-timeseries "));
			} else if (xrstf::startsWith(commandStr, "clear-time-series ")) {
				handleClearTimeSeriesCommand(commandStr + strlen("clear-time-series "));
			} else if (xrstf::startsWith(commandStr, "set-time-series-points ")) {
				handleSetTimeSeriesPointsCommand(commandStr + strlen("set-time-series-points "));
			} else if (xrstf::startsWith(commandStr, "disable-timeseries")) {
				handleDisableTimeSeriesCommand();
			} else if (xrstf::startsWith(commandStr, "disable-time-series")) {
				handleDisableTimeSeriesCommand();
			} else if (xrstf::startsWith(commandStr, "set-batch-size ")) {
				handleSetBatchSizeCommand(commandStr + strlen("set-batch-size "));
			} else if (strcmp(commandStr, "ntp-time") == 0) {
				handleGetNTPTimeCommand();
			} else if (strcmp(commandStr, "show-timeseries") == 0) {
				handleShowTimeSeriesCommand(NULL);
			} else if (strcmp(commandStr, "show-time-series") == 0) {
				handleShowTimeSeriesCommand(NULL);
			} else if (strcmp(commandStr, "clear-timeseries") == 0) {
				handleClearTimeSeriesCommand(NULL);
			} else if (strcmp(commandStr, "clear-time-series") == 0) {
				handleClearTimeSeriesCommand(NULL);
			} else if (strcmp(commandStr, "clear-all-timeseries") == 0) {
				handleClearAllTimeSeriesCommand();
			} else if (strcmp(commandStr, "clear-all-time-series") == 0) {
				handleClearAllTimeSeriesCommand();
			} else if (strcmp(commandStr, "enable-webserver") == 0) {
				handleEnableWebserverCommand();
			} else if (strcmp(commandStr, "disable-webserver") == 0) {
				handleDisableWebserverCommand();
			} else if (strcmp(commandStr, "enable-wifi") == 0) {
				handleEnableWifiCommand();
			} else if (strcmp(commandStr, "disable-wifi") == 0) {
				handleDisableWifiCommand();
			} else if (strcmp(commandStr, "enable-led") == 0) {
				handleEnableLEDCommand();
			} else if (strcmp(commandStr, "disable-led") == 0) {
				handleDisableLEDCommand();
			} else if (strcmp(commandStr, "local-ip") == 0) {
				handleLocalIPCommand();
			} else if (strcmp(commandStr, "wipe") == 0) {
				handleWipeCommand();
			} else if (strcmp(commandStr, "battery") == 0) {
				handleBatteryCommand();
			} else if (strcmp(commandStr, "reboot") == 0 || strcmp(commandStr, "restart") == 0 || strcmp(commandStr, "reset") == 0) {
				handleRestartCommand();
			} else if (strcmp(commandStr, "config") == 0 || strcmp(commandStr, "show-configuration") == 0) {
				handleShowConfigurationCommand();
			} else if (strcmp(commandStr, "measure") == 0) {
				handleMeasureCommand();
			} else if (strcmp(commandStr, "ota") == 0) {
				handleOTACommand(NULL);
			} else if (xrstf::startsWith(commandStr, "ota ")) {
				handleOTACommand(commandStr + strlen("ota "));
			} else {
				xrstf::serialPrintf("Error: unknown command '%s'\n", commandStr);
			}

			clear();
		}
	}
} // namespace cli
