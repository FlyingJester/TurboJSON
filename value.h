#pragma once
#include <stdio.h>

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
        char *string;
        struct Turbo_Value *array;
        struct Turbo_Property *object;
        struct { const char *message, *str, *at; } error;
    } value;
};

const char *Turbo_Value(struct Turbo_Value *to, const char *in, const char *const end);
void Turbo_WriteValue(struct Turbo_Value *that, FILE *out, int level);

#ifdef __cplusplus
}
#endif
