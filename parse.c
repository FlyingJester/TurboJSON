#include "parse.h"
#include "whitespace.h"
#include "object.h"
#include "array.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>

int TurboJSON(struct Turbo_Value *to, const char *in, const char *end){
    if(end==NULL){
        end = in+strlen(in);
    }
    
    in+=SkipWhitespace(in, end-in);
    if(*in=='[')
        return Turbo_Array(to, in, end)!=NULL;
    if(*in=='{')
        return Turbo_Object(to, in, end)!=NULL;

    Turbo_Error(to, in, "Expected Object or Array as root");
    return 0;
}

int TurboFree(struct Turbo_Value *that){
    unsigned i = 0;
    switch(that->type){
        case TJ_Error:
            free((void *)that->value.error->message);
            free(that->value.error);
            return 0;
        case TJ_Array:
            while (i < that->length) {
                TurboFree(that->value.array + i);
                i++;
            }
            free(that->value.array);
            that->value.array = NULL;
            return that->length = 0;
        case TJ_Object:
            while (i < that->length) {
                TurboFree(&that->value.object[i].value);
                i++;
            }
            free(that->value.object);
            that->value.object = NULL;
            return that->length = 0;
        case TJ_String:
            free((void*)that->value.string);
            that->value.string = NULL;
            return that->length = 0;
        default:
            return that->length = 0;
    }
}
