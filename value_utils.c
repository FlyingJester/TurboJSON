#include "value.h"
#include "number.h"
#include "string.h"
#include "array.h"
#include "object.h"
#include "error.h"
#include "literal_atom.h"
#include <assert.h>

const char *Turbo_ValueUtil(struct Turbo_Value * __restrict__ to, const char *in, const char *const end){
    
    if(TrueAtom(in)){
        to->type = TJ_Boolean;
        to->value.boolean = 1;
        return in + 4;
    }
    else if(FalseAtom(in)){
        to->type = TJ_Boolean;
        to->value.boolean = 0;
        return in + 5;
    }
    else if(NullAtom(in)){
        to->type = TJ_Null;
        return in + 4;
    }
    return Turbo_Error(to, in, "Expected Value");
}

void Turbo_WriteValue(struct Turbo_Value *that, FILE *out, int level){
    switch(that->type){
        case TJ_Boolean:
            if(that->value.boolean)
                fputs("true", out);
            else
                fputs("false", out);
            return;
        case TJ_Null:
            fputs("null", out);
            return;
        case TJ_Error:
            Turbo_WriteError(that, out, level);
            return;
        case TJ_String:
            Turbo_WriteString(that, out, level);
            return;
        case TJ_Number:
            Turbo_WriteNumber(that, out, level);
            return;
        case TJ_Object:
            Turbo_WriteObject(that, out, level);
            return;
        case TJ_Array:
            Turbo_WriteArray(that, out, level);
            return;
    }
    assert(0);
}
