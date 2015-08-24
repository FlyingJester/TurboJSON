#include "string.h"
#include "find_quote.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const char *Turbo_StringCopy(struct Turbo_Value *to, const char *in, const char *const end){
    if(end){}

    to->type = TJ_String;

    assert(*in=='"');
    in++;
    {
        const uint64_t length = FindQuote(in);
        const char * const next = in + length;
        
        assert(next[-1]!='\\');
        if(next[0]!='"')
            return NULL;
        
        {
            char *n = malloc(length+1);
            n[length] = 0;
            memcpy(n, in, length);
            to->value.string = n;
        }
        to->length = length;
        return next+1;
    }
}


const char *Turbo_String(struct Turbo_Value *to, const char *in, const char *const end){
    if(end){}

    to->type = TJ_String;

    assert(*in=='"');
    in++;
    {
        const uint64_t length = FindQuote(in);
        const char * const next = in + length;
        
        assert(next[-1]!='\\');
        if(next[0]!='"')
            return NULL;
        
        to->value.string = in;
        to->length = length;
        
        return next+1;
    }
}

void Turbo_WriteString(struct Turbo_Value *that, FILE *out, int level){
    if(level){}
    assert(that->type == TJ_String);
    fputc('"', out);
    fwrite(that->value.string, 1, that->length, out);
    fputc('"', out);
}
