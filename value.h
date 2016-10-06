#pragma once
#include <stdio.h>

#ifdef _MSC_VER
#define __restrict__ __restrict
#elif defined __WATCOMC__
#define __restrict__
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum Turbo_Type {TJ_Error, TJ_String, TJ_Number, TJ_Object, TJ_Array, TJ_Boolean, TJ_Null};

struct Turbo_Value{
    enum Turbo_Type type;
    unsigned length;
    union{
        double number;
        int boolean;
        const char *string;
        struct Turbo_Value *array;
        struct Turbo_Property *object;
        struct Turbo_Error *error;
    } value;
};

const char *Turbo_Value(struct Turbo_Value * __restrict__ to, const char *in, const char *const end);
void Turbo_WriteValue(struct Turbo_Value *that, FILE *out, int level);

#ifdef __cplusplus
}
#endif
