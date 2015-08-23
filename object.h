#pragma once
#include "value.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

struct Turbo_Property {
    const char *name;
    unsigned name_length;
    struct Turbo_Value value;
};

const char *Turbo_Object(struct Turbo_Value *to, const char *in, const char *const end);
void Turbo_WriteObject(struct Turbo_Value *that, FILE *out, int level);

#ifdef __cplusplus
}
#endif
