#pragma once

#include <stdint.h>
#include <stdio.h>

#define SET_BIT(byte, pos)    (byte |= (1U << (pos)))
#define CLEAR_BIT(byte, pos)  (byte &= (~(1U << (pos))))
#define TOGGLE_BIT(byte, pos) (byte ^= (1U << (pos)))
#define CHECK_BIT(byte, pos)  (byte & (1UL << (pos)))

#define SET_BIT_TO_VALUE(byte, pos, high) (high ? SET_BIT(byte, pos) : CLEAR_BIT(byte, pos))

namespace xrstf {
	// This function flips the N least significant bits.
	// All more significant bits are kept. Use bitSize=8
	// to flip all bits.
	uint8_t flipLSB(uint8_t value, uint8_t bitSize);

	bool startsWith(const char *a, const char *b);
	bool safeStringToInt(const char *value, int *out);

	size_t hexdecode(char *buf, size_t length, const char *string);
	void hexencode(const char *input, size_t length, char *out);

	void decToBinary(char *buf, uint8_t value);
	char *fmtBinary(uint8_t value);

	char *fmtFloat(float value, uint8_t decimals = 2);

	int stricmp(char const *a, char const *b);

	// to collect len bytes of output, input needs to have at least 2*len bytes
	bool normalizeFingerprint(const char *input, size_t len, char *out);
} // namespace xrstf
