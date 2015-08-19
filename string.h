#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t find_quote(const char *in, unsigned length);
/* returns 0 for different, 1 for same */ 
uint64_t compare_strings(const char *in, const char *to, uint64_t to_length);

#ifdef __cplusplus
}
#endif
