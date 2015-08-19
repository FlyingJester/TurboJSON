#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/* Prefixed versions do NOT have '0', '0x', or '0b' in their strings, or a '-' or '+' in front.
 * They may also leave `dest' in an inconsistent state on error. */
int64_t DecStrToNumber(const char *string, uint64_t *length);
int64_t HexStrToNumber(const char *string, uint64_t *length);
int64_t OctStrToNumber(const char *string, uint64_t *length);
int64_t BinStrToNumber(const char *string, uint64_t *length);

/* These basically just check for a leading 0 or 0x */
int IsHex(const char *string);
int IsOct(const char *string);

int IsDecDigit(char c);
int IsHexDigit(char c);
int IsOctDigit(char c);
int IsBinDigit(char c);

double s_CreateFloat(uint64_t Whole, uint64_t Decimal, uint64_t Places);

int ParseNumber(const char *in, double *out);

#ifdef __cplusplus
}
#endif
