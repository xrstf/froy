#include "ota.h"
#include "config.h"
#include "eeprom.h"
#include <ESP8266httpUpdate.h>
#include <WiFiClient.h>
#include <xrstf_arduino_util.h>
#include <xrstf_util.h>

namespace ota {
	struct url {
		String scheme;
		String host;
		uint16_t port;
		String path;
	};

	// this does not support IPv6
	bool parseURL(url *result, String &input) {
		// find scheme
		int schemeEnd = input.indexOf(':');
		if (schemeEnd < 0) {
			return false;
		}

		result->scheme = input.substring(0, schemeEnd);
		result->port   = 80;
		result->path   = "";
		result->host   = "";

		if (result->scheme.compareTo("https") == 0) {
			result->port = 443;
		}

		// trim trailing slashes
		while (input.endsWith("/")) {
			input = input.substring(0, input.length() - 1);
		}

		int hostStart = schemeEnd + 3; // skip "://"

		// find optional (but highly likely) path
		int pathStart = input.indexOf('/', hostStart);
		if (pathStart == -1) {
			result->host = input.substring(hostStart);
		} else {
			result->host = input.substring(hostStart, pathStart);
			result->path = input.substring(pathStart);
		}

		// find explicit port in hostname
		int portStart = result->host.indexOf(':');
		if (portStart > 0) {
			result->port = result->host.substring(portStart + 1).toInt();
			result->host = result->host.substring(0, portStart);
		}

		return true;
	}

	void update(String &endpointURL, String &constraint, char fingerprint[eeprom::FINGERPRINT_BYTES]) {
		if (constraint.equals(FROY_VERSION)) {
			xrstf::serialPrintf("[OTA] Constraint equals current version, skipping.");
			return;
		}

		if (constraint.length() > 0) {
			endpointURL += "/" + constraint;
		}

		xrstf::serialPrintf("[OTA] Checking %s\n", endpointURL.c_str());

		t_httpUpdate_return ret;

		if (xrstf::startsWith(endpointURL.c_str(), "https://")) {
			BearSSL::WiFiClientSecure client;

			if (eeprom::hasFingerprint(fingerprint)) {
				if (!client.setFingerprint((uint8_t *)fingerprint)) {
					Serial.println("Failed setting fingerprint.");
				}
			} else {
				client.setInsecure();
			}

			ret = ESPhttpUpdate.update(client, endpointURL, FROY_VERSION);
		} else {
			WiFiClient client;
			ret = ESPhttpUpdate.update(client, endpointURL, FROY_VERSION);
		}

		switch (ret) {
		case HTTP_UPDATE_FAILED:
			Serial.println("[OTA] Update failed.");
			break;
		case HTTP_UPDATE_NO_UPDATES:
			Serial.println("[OTA] Update has no new version available.");
			break;
		case HTTP_UPDATE_OK:
			Serial.println("[OTA] Update ok."); // may not be called since we reboot the ESP
			break;
		}
	}
} // namespace ota
