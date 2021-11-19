#pragma once

#include <LittleFS.h>

class Datalogger {
public:
	// keep directory as short as possible, as the total filepath is
	// limited to 31 characters, and this class needs 5 of those for
	// itself already.
	Datalogger(FS &fs, String directory);

	bool begin();
	void end();
	bool hasMetric(const String &metric);
	bool appendData(const String &metric, const String &data);
	bool appendData(const String &metric, const char *data, size_t length);
	bool printMetric(const String &metric);
	bool removeMetric(const String &metric);
	bool wipe();
	size_t availableSpace();
	void metricFilename(char *buf, const String &metric);

private:
	FS &fs;
	String directory;

	size_t maxMetricLength();
};
