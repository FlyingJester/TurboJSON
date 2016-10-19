#include "object.h"
#include "whitespace.h"
#include "find_quote.h"
#include "error.h"
#include "value.h"
#include "string.h"
#include <assert.h>
#include <stdlib.h>

#define INIT_CAPACITY 4

const char *Turbo_Object(struct Turbo_Value * __restrict__ to, const char *in, const char *const end){
    assert(*in=='{');
    in++;

    to->type = TJ_Object;

    in+=SkipWhitespace(in, end-in);

    to->length = 0;

    if(*in=='}'){
        to->value.object = NULL;
        return in+1;
        puts("Empty object");
    }
    else{
        
        unsigned capacity = INIT_CAPACITY;
        struct Turbo_Property *values = malloc(sizeof(struct Turbo_Property) * INIT_CAPACITY);
        
        do{
            const char *next;
            to->length++;
            if(to->length >= capacity){
                capacity<<=1;
                values = realloc(values, sizeof(struct Turbo_Property) * capacity);
            }
            {
                in+=SkipWhitespace(in, end-in);
                if(in[0]!='"')
                    goto fail;

                in++;

                values[to->length-1].name_length = FindQuote(in, end - in);

                values[to->length-1].name = in;
                next = in+values[to->length-1].name_length+1;       
                assert(next[-2]!='\\');

                if(next[-1]!='"')
                    goto fail;       
            }
            
            in = next + SkipWhitespace(next, end-in);

            if(*in!=':'){
                Turbo_Error(to, in, "Expected ':' after object property name");
                goto fail;
            }
            in++;
            
            in+=SkipWhitespace(in, end-in);

            if((next = Turbo_Value(&(values[to->length-1].value), in+SkipWhitespace(in, end-in), end))==0)
                goto fail;
            
            in = next + SkipWhitespace(next, end-in);
            
            if(*in!=',')
                break;
            in++;
            
            in+=SkipWhitespace(in, end-in);
            
        }while(1);

        if(*in!='}'){
            free(values);
            return Turbo_Error(to, in, "Expected ',' or '}' after element of array");
        }
        
        to->value.object = values;
        
        return in+1;
fail:
        puts("Fail");
        free(values);
        return NULL;
    }
}

void Turbo_WriteObject(struct Turbo_Value *that, FILE *out, int level){
    unsigned i = 0;
    assert(that->type == TJ_Object);
    fputc('{', out);
    fputc('\n', out);
    
    while(i<that->length){
        if(i){
            fputc(',', out);
            fputc('\n', out);
        }
        {
            int e = level;
            while(e--)
                fputc('\t', out);
        }
        fprintf(out, "\"%s\":", that->value.object[i].name);
        
        Turbo_WriteValue(&(that->value.object[i].value), out, level + 1);
        
        i++;
    }   
    fputc('\n', out);
    {
        int e = level;
        if(e>1)
            while(--e)
                fputc('\t', out);
    }
    fputc('}', out);
}
