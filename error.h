#pragma once
#include "value.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Turbo_Error{
    const char *message, *str, *at; 
};

const char *Turbo_Error(struct Turbo_Value *to, const char *in, const char * message);
void Turbo_WriteError(struct Turbo_Value *that, FILE *out, int level);

#ifdef __cplusplus
}
#endif
