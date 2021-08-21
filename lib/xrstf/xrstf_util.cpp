#include "xrstf_util.h"
#include <cmath>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

namespace xrstf {
	uint8_t flipLSB(uint8_t value, uint8_t bitSize) {
		uint8_t ret = value;

		if (bitSize > 8) {
			bitSize = 8;
		}

		for (uint8_t i = 0; i < bitSize; ++i) {
			SET_BIT_TO_VALUE(ret, (bitSize - 1) - i, CHECK_BIT(value, i));
		}

		return ret;
	}

	bool startsWith(const char *a, const char *b) {
		if (strncmp(a, b, strlen(b)) == 0)
			return 1;
		return 0;
	}

	bool safeStringToInt(const char *value, int *out) {
		*out = atoi(value);

		// convert back to a number
		char buf[33];
		sprintf(buf, "%d", *out);

		return strcmp(value, buf) == 0;
	}

	size_t hexdecode(char *buf, size_t length, const char *string) {
		size_t slength = strlen(string);
		if (slength % 2 != 0) { // must be even
			return 0;
		}

		size_t dlength   = slength / 2;
		size_t maxlength = dlength < length ? dlength : length;
		size_t index     = 0;

		while (index < maxlength * 2) {
			char c    = string[index];
			int value = 0;

			if (c >= '0' && c <= '9') {
				value = (c - '0');
			} else if (c >= 'A' && c <= 'F') {
				value = (10 + (c - 'A'));
			} else if (c >= 'a' && c <= 'f') {
				value = (10 + (c - 'a'));
			} else {
				return index;
			}

			buf[(index / 2)] += value << (((index + 1) % 2) * 4);

			index++;
		}

		return index;
	}

	void hexencode(const char *input, size_t length, char *out) {
		size_t i;
		for (i = 0; i < length; i++) {
			sprintf(out + (i * 2), "%02x", (unsigned char)input[i]);
		}
		out[i * 2] = 0;
	}

	void decToBinary(char *buf, uint8_t value) {
		for (uint8_t i = 0; i < 8; ++i) {
			buf[i] = CHECK_BIT(value, 7 - i) ? '1' : '0';
		}

		buf[8] = '\0';
	}

	char evilSharedFmtBinaryBuffer[9];
	char *fmtBinary(uint8_t value) {
		decToBinary(evilSharedFmtBinaryBuffer, value);
		return evilSharedFmtBinaryBuffer;
	}

	char evilSharedFmtFloatBuffer[16];
	char *fmtFloat(float value, uint8_t decimals) {
		int main = (int)value;
		int dec  = (int)((value - main) * ((int)pow(10, decimals)));

		if (dec < 0) {
			dec = -dec;
		}

		while (dec != 0 && dec % 10 == 0) {
			dec /= 10;
		}

		sprintf(evilSharedFmtFloatBuffer, "%d.%d", main, dec);
		return evilSharedFmtFloatBuffer;
	}

	// thanks to https://stackoverflow.com/a/5820991
	int stricmp(char const *a, char const *b) {
		for (;; a++, b++) {
			int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
			if (d != 0 || !*a) {
				return d;
			}
		}
	}

	bool normalizeFingerprint(const char *input, size_t len, char *out) {
		memset(out, 0, len);

		char *buf = (char *)malloc(len * 2 + 1);
		if (buf == NULL) {
			return false;
		}
		memset(buf, 0, len * 2 + 1);

		const char *p;
		size_t collected = 0;
		for (p = input; *p != '\0'; p++) {
			if (isxdigit(*p)) {
				buf[collected] = *p;
				collected++;

				if (collected >= len * 2) {
					break;
				}
			}
		}

		if (collected != len * 2) {
			delete buf;
			return false;
		}

		size_t decoded = hexdecode(out, collected, buf);
		delete buf;

		return decoded == collected;
	}
} // namespace xrstf
