#include "array.h"
#include "whitespace.h"
#include "error.h"
#include "value.h"
#include <assert.h>
#include <stdlib.h>

#define INIT_CAPACITY 8

const char *Turbo_Array(struct Turbo_Value * __restrict__ to, const char *in, const char *const end){
    assert(*in=='[');
    in++;

    to->type = TJ_Array;

    in+=SkipWhitespace(in, end-in);

    to->length = 0;

    if(*in==']'){
        to->value.array = NULL;
        return in+1;
    }
    else{
        unsigned capacity = INIT_CAPACITY;
        struct Turbo_Value *values = malloc(sizeof(struct Turbo_Value) * INIT_CAPACITY);
        
        do{
            const char *next;
            to->length++;
            if(to->length > capacity){
                capacity<<=2;
                values = realloc(values, sizeof(struct Turbo_Value) * capacity);
            }
            
            if((next = Turbo_Value(&(values[to->length-1]), in+SkipWhitespace(in, end-in), end))==0){
                free(values);
                return NULL;
            }
            in = next + SkipWhitespace(next, end-in);
            
            if(*in!=',')
                break;
            
            in++;
            in+= SkipWhitespace(in, end-in);
            
        }while(1);

        if(*in!=']'){
            free(values);
            return Turbo_Error(to, in, "Expected ',' or '}' after element of array");
        }
        
        to->value.array = values;
        
        return in+1;
    }
}

void Turbo_WriteArray(struct Turbo_Value *that, FILE *out, int level){
    unsigned i = 0;
    assert(that->type == TJ_Array);

    fputc('[', out);
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
        
        Turbo_WriteValue(&(that->value.array[i]), out, level + 1);
        
        i++;
    }   
    fputc('\n', out);
    {
        int e = level;
        if(e>1)
            while(--e)
                fputc('\t', out);
    }
    fputc(']', out);
}
