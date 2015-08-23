#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t FindQuote(const char *in);
/* returns 0 for different, 1 for same */ 
int CompareStrings(const char *in, const char *to, uint64_t to_length);

#ifdef __cplusplus
}
#endif
