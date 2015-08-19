#include "parse_number.h"

/* Prefixed versions do NOT have '0', '0x', or '0b' in their strings, or a '-' or '+' in front.
 * They may also leave `dest' in an inconsistent state on error. */
/*
int DecStrToNumber(const char *string, int64_t *dest){
    int64_t i = 0;
    while(IsDecDigit(*string)){
        i *= 10;
        i += *string - '0';
        string++;
    }
    dest[0] = i;
}

int HexStrToNumber(const char *string, int64_t *dest);
int OctStrToNumber(const char *string, int64_t *dest);
int BinStrToNumber(const char *string, int64_t *dest);
*/

/* These basically just check for a leading 0 or 0x */
int IsHex(const char *string);
int IsOct(const char *string);

int IsDecDigit(char c);
int IsHexDigit(char c);
int IsOctDigit(char c);
int IsBinDigit(char c);

double s_CreateFloat(uint64_t Whole, uint64_t Decimal, uint64_t Places);

int ParseNumber(const char *in, double *out);