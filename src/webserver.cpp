#include "webserver.h"
#include "config.h"
#include "eeprom.h"
#include "multimeter.h"
#include "ota.h"
#include "sensor.h"
#include "util.h"
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

namespace webserver {
	ESP8266WebServer server(80);
	bool running;

	bool prepareRequest(struct eeprom::data *data) {
		eeprom::load(data);

		if (data->sensorType == 0x0) {
			server.send(503, "text/plain", "No sensor type configured yet.\r\n");
			return false;
		}

		if (data->sensorAddress == 0x0) {
			server.send(503, "text/plain", "No I2C address configured yet.\r\n");
			return false;
		}

		if (!sensor::setup(data)) {
			Serial.println("Failed to setup BME sensor :(");
			server.send(503, "text/plain", "Failed to setup sensor.\r\n");
			return false;
		}

		return true;
	}

	void handleDataRequest() {
		eeprom::data config;
		if (!prepareRequest(&config)) {
			return;
		}

		multimeter::measurement m;
		multimeter::read(&m, &config);

		StaticJsonDocument<384> doc;

		doc["deviceName"]         = config.deviceName;
		doc["appVersion"]         = FROY_VERSION;
		doc["sensorType"]         = sensor::typeName(config.sensorType);
		doc["temperature"]        = m.sensor.temperature;
		doc["pressure"]           = m.sensor.pressure;
		doc["humidity"]           = m.sensor.humidity;
		doc["temperatureOffset"]  = config.temperatureOffset;
		doc["pressureOffset"]     = config.pressureOffset;
		doc["humidityOffset"]     = config.humidityOffset;
		doc["temperatureRetries"] = m.sensor.temperatureRetries;
		doc["pressureRetries"]    = m.sensor.pressureRetries;
		doc["humidityRetries"]    = m.sensor.humidityRetries;
		doc["battery"]            = m.battery;
		doc["batteryRaw"]         = m.batteryRaw;

		String body;
		serializeJson(doc, body);

		server.keepAlive(false);
		server.send(200, "application/json", body);
	}

	void handleMetricsRequest() {
		struct eeprom::data config;
		if (!prepareRequest(&config)) {
			return;
		}

		multimeter::measurement m;
		multimeter::read(&m, &config);

		String response        = "";
		const char *sensorType = sensor::typeName(config.sensorType);

		char buf[192];
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_info{device_name=\"%s\",sensor=\"%s\",version=\"%s\"} 1\r\n", config.deviceName, sensorType, FROY_VERSION);

		response += "# HELP froy_info Information about this device.\r\n";
		response += "# TYPE froy_info gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_temperature{device_name=\"%s\"} %f\r\n", config.deviceName, m.sensor.temperature);

		response += "# HELP froy_temperature The current temperature in degress Celsius.\r\n";
		response += "# TYPE froy_temperature gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_temperature_retries{device_name=\"%s\"} %d\r\n", config.deviceName, m.sensor.temperatureRetries);

		response += "# HELP froy_temperature_retries How many tries it took to read the temperature.\r\n";
		response += "# TYPE froy_temperature_retries gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_temperature_offset{device_name=\"%s\"} %f\r\n", config.deviceName, config.temperatureOffset);

		response += "# HELP froy_temperature_offset The calibrated offset value for the temperature.\r\n";
		response += "# TYPE froy_temperature_offset gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_pressure{device_name=\"%s\"} %f\r\n", config.deviceName, m.sensor.pressure);

		response += "# HELP froy_pressure The current air pressure in hPa.\r\n";
		response += "# TYPE froy_pressure gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_pressure_retries{device_name=\"%s\"} %d\r\n", config.deviceName, m.sensor.pressureRetries);

		response += "# HELP froy_pressure_retries How many tries it took to read the pressure.\r\n";
		response += "# TYPE froy_pressure_retries gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_pressure_offset{device_name=\"%s\"} %f\r\n", config.deviceName, config.pressureOffset);

		response += "# HELP froy_pressure_offset The calibrated offset value for the pressure.\r\n";
		response += "# TYPE froy_pressure_offset gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_humidity{device_name=\"%s\"} %f\r\n", config.deviceName, m.sensor.humidity);

		response += "# HELP froy_humidity The relative humidity in percent.\r\n";
		response += "# TYPE froy_humidity gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_humidity_retries{device_name=\"%s\"} %d\r\n", config.deviceName, m.sensor.humidityRetries);

		response += "# HELP froy_humidity_retries How many tries it took to read the humidity.\r\n";
		response += "# TYPE froy_humidity_retries gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_humidity_offset{device_name=\"%s\"} %f\r\n", config.deviceName, config.humidityOffset);

		response += "# HELP froy_humidity_offset The calibrated offset value for the humidity.\r\n";
		response += "# TYPE froy_humidity_offset gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_measurement_duration_ms{device_name=\"%s\"} %d\r\n", config.deviceName, m.duration);

		response += "# HELP froy_measurement_duration The time it took to perform the measurement.\r\n";
		response += "# TYPE froy_measurement_duration gauge\r\n";
		response += buf;

		memset(buf, 0, sizeof(buf));
		sprintf(buf, "froy_battery{device_name=\"%s\"} %d\r\n", config.deviceName, m.battery);

		response += "# HELP froy_battery The raw ADC output value for the battery voltage.\r\n";
		response += "# TYPE froy_battery gauge\r\n";
		response += buf;

		server.keepAlive(false);
		server.send(200, "text/plain", response);
	}

	void handleGetConfigurationRequest() {
		LOAD_EEPROM(config);

		StaticJsonDocument<192> doc;

		doc["appVersion"]        = FROY_VERSION;
		doc["dataVersion"]       = config.version;
		doc["deviceName"]        = config.deviceName;
		doc["sensorType"]        = sensor::typeName(config.sensorType);
		doc["sensorAddress"]     = config.sensorAddress;
		doc["enableLED"]         = config.enableLED;
		doc["pushURL"]           = config.pushURL;
		doc["ssid"]              = config.ssid;
		doc["temperatureOffset"] = config.temperatureOffset;
		doc["pressureOffset"]    = config.pressureOffset;
		doc["humidityOffset"]    = config.humidityOffset;

		// disable sensor reading
		config.sensorType = 0x0;

		// read battery
		multimeter::measurement m;
		multimeter::read(&m, &config);

		doc["battery"] = m.battery;

		String body;
		serializeJson(doc, body);

		server.keepAlive(false);
		server.send(200, "application/json", body);
	}

	void handleUpdateConfigurationRequest() {
		LOAD_EEPROM(config);

		server.keepAlive(false);

		// server.arg("plain") reads the raw request body, a JSON string
		// in our case; this has nothing to do with multipart encoding
		if (eeprom::updateFromJSON(&config, server.arg("plain"), NULL)) {
			server.send(200, "text/plain", "OK");
		} else {
			server.send(400, "text/plain", "Configuration was invalid.");
		}
	}

	void handleRestartRequest() {
		server.keepAlive(false);

		if (server.method() == HTTP_POST) {
			server.send(200, "text/plain", "OK");
			scheduleRestart();
		} else {
			server.send(400, "text/plain", "Must use POST method.");
		}
	}

	void handleOTARequest() {
		server.keepAlive(false);

		if (server.method() == HTTP_POST) {
			LOAD_EEPROM(config);

			if (strlen(config.otaURL) == 0) {
				server.send(409, "text/plain", "No OTA URL configured.");
				return;
			}

			String url(config.otaURL);
			String constraint(server.arg("constraint"));

			ota::update(url, constraint, config.otaFingerprint);
			server.send(503, "text/plain", "If you can see this, the OTA update failed. Sorry.");
		} else {
			server.send(400, "text/plain", "Must use POST method.");
		}
	}

	void ledWrapper(void (*handler)(void)) {
		LOAD_EEPROM(data);

		if (data.enableLED) {
			enableLED();
		}

		handler();

		if (data.enableLED) {
			disableLED();
		}
	}

	void setup() {
		server.on("/data", []() { ledWrapper(handleDataRequest); });
		server.on("/metrics", []() { ledWrapper(handleMetricsRequest); });
		server.on("/ota", []() { ledWrapper(handleOTARequest); });
		server.on("/config", []() {
			ledWrapper([]() {
				switch (server.method()) {
				case HTTP_GET:
					handleGetConfigurationRequest();
					break;

				case HTTP_POST:
					handleUpdateConfigurationRequest();
					break;

				default:
					server.send(400, "text/plain", "invalid method, allowed: GET, POST");
				}
			});
		});

		server.on("/reboot", handleRestartRequest);
		server.on("/restart", handleRestartRequest);
		server.on("/reset", handleRestartRequest);
	}

	void start() {
		LOAD_EEPROM(data);

		if (data.enableWebserver) {
			server.begin();
			Serial.println("HTTP server started on port 80.");
			running = true;
		}
	}

	void stop() {
		if (running) {
			server.stop();
			Serial.println("HTTP server stopped.");
			running = false;
		}
	}

	void handleRequests() {
		if (running) {
			server.handleClient();
		}
	}
} // namespace webserver
