#pragma once
#include "value.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

const char *Turbo_String(struct Turbo_Value * __restrict__ to, const char *in, const char *const end);
const char *Turbo_StringCopy(struct Turbo_Value *to, const char *in, const char *const end);
void Turbo_WriteString(struct Turbo_Value *that, FILE *out, int level);

#ifdef __cplusplus
}
#endif
