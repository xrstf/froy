#include "datalogger.h"
#include <Arduino.h>
#include <Wire.h>

Datalogger::Datalogger(FS &fs, String directory) : fs(fs), directory(directory) {
}

bool Datalogger::begin() {
	if (!this->fs.begin()) {
		Serial.println("An Error has occurred while mounting LittleFS.");
		Serial.println("Did you set the partioning parameters (ldscript) correctly?");
#ifndef DEBUG_ESP_CORE
		Serial.println("Define DEBUG_ESP_CORE to see more information.");
#endif
		return false;
	}

	return true;
}

void Datalogger::end() {
	this->fs.end();
}

size_t Datalogger::availableSpace() {
	FSInfo info;
	if (!this->fs.info(info)) {
		Serial.println("Failed to get FS info.");
		return 0;
	}

	return info.totalBytes - info.usedBytes;
}

void Datalogger::metricFilename(char *buf, const String &metric) {
	sprintf(buf, "%s/%s.csv", this->directory.c_str(), metric.c_str());
}

size_t Datalogger::maxMetricLength() {
	return ((31 - 4) /* ".csv" */ - 1 /* "/" */) - this->directory.length();
}

bool Datalogger::appendData(const String &metric, const String &data) {
	if (this->availableSpace() < data.length()) {
		Serial.println("Not enough free disk space for this data.");
		return false;
	}

	// https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html#littlefs-file-system-limitations
	if (metric.length() > this->maxMetricLength()) {
		Serial.println("Metric name is too long.");
		return false;
	}

	char filename[32];
	this->metricFilename(filename, metric);

	File f = this->fs.open(filename, "a");
	if (!f) {
		Serial.println("Failed to open file.");
		return false;
	}

	size_t written = f.println(data);
	f.close();

	if (written < data.length()) {
		Serial.println("Failed to write full data set.");
		return false;
	}

	return true;
}

bool Datalogger::printMetric(const String &metric) {
	// https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html#littlefs-file-system-limitations
	if (metric.length() > this->maxMetricLength()) {
		Serial.println("Metric name is too long.");
		return false;
	}

	char filename[32];
	this->metricFilename(filename, metric);

	if (!this->fs.exists(filename)) {
		Serial.println("File does not exist.");
		return true;
	}

	File f = this->fs.open(filename, "r");
	if (!f) {
		Serial.println("Failed to open file.");
		return false;
	}

	char buf[128];
	memset(buf, 0, sizeof(buf));

	while (f.available()) {
		f.readBytes(buf, sizeof(buf)-1);
		Serial.write(buf);
	}

	f.close();

	return true;
}

bool Datalogger::removeMetric(const String &metric) {
	// https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html#littlefs-file-system-limitations
	if (metric.length() > this->maxMetricLength()) {
		Serial.println("Metric name is too long.");
		return false;
	}

	char filename[32];
	this->metricFilename(filename, metric);

	if (this->fs.exists(filename)) {
		return this->fs.remove(filename);
	}

	return true;
}

bool Datalogger::wipe() {
	if (this->fs.exists(this->directory.c_str())) {
		return this->fs.rmdir(this->directory.c_str());
	}

	return true;
}
