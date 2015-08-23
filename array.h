#pragma once
#include "value.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

const char *Turbo_Array(struct Turbo_Value *to, const char *in, const char *const end);
void Turbo_WriteArray(struct Turbo_Value *that, FILE *out, int level);

#ifdef __cplusplus
}
#endif
