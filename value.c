#include "value.h"
#include "number.h"
#include "string.h"
#include "array.h"
#include "object.h"
#include "error.h"
#include "literal_atom.h"
#include <assert.h>

/*
int TrueAtom(const char *in);
int FalseAtom(const char *in);
int NullAtom(const char *in);
*/

/* TODO: These are small routines that should probably become inline ASM.
 *
 * Alternatively, this entire function could benefit from being remade as
 * a series of jumps to Turbo_String, Turbo_Array, etc. rather than calls.
 * Similarly, we could then pull in the Atom sources, or use a subset 
 * calling convention for them.
 */

const char *Turbo_Value(struct Turbo_Value *to, const char *in, const char *const end){
    
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
    switch(*in){
        case '"':
        return Turbo_StringCopy(to, in, end);
        case '[':
        return Turbo_Array(to, in, end);
        case '{':
        return Turbo_Object(to, in, end);
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        return Turbo_Number(to, in, end);
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

