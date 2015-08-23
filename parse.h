#pragma once
#include "value.h"

#ifdef __cplusplus
extern "C" {
#endif

int TurboJSON(struct Turbo_Value *to, const char *in, const char *end);
#define Turbo_Parse TurboJSON
int TurboFree(struct Turbo_Value *that);
#define Turbo_FreeParse TurboFree

#ifdef __cplusplus
}
#endif
