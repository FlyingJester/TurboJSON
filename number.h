#pragma once
#include "value.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif


#define TURBO_IS_STARTING_DIGIT(X) ((X == '-') || ((X>='0') && (X<='9')))

const char *Turbo_Number(struct Turbo_Value *to, const char *in, const char *const end);
void Turbo_WriteNumber(struct Turbo_Value *that, FILE *out, int level);

#ifdef __cplusplus
}
#endif
