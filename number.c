#include "number.h"
#include "number_literal.h"
#include <stdio.h>
#include <assert.h>

const char *Turbo_Number(struct Turbo_Value *to, const char *in, const char *const end){
    if(end){}
    assert( TURBO_IS_STARTING_DIGIT(*in) );
    to->value.number = NumberLiteral(&in);
    to->type = TJ_Number;
    return in;
}

void Turbo_WriteNumber(struct Turbo_Value *that, FILE *out, int level){
    long i;
    if(level){}
    assert(that->type == TJ_Number);
    
    i = that->value.number;
    if(i==that->value.number){
        fprintf(out, "%li", i);
    }
    else
        fprintf(out, "%f", that->value.number);
}
