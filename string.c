#include "string.h"
#include "find_quote.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static void encode_string(const char *in, char *to, uint64_t length, uint64_t *out_length) {
    uint64_t i = 0, at = 0;

    while (i < length) {
        if (in[i] == '\\') {
            if (++i == length) {
                assert(0 && "Escaped quote is the termintor of a string literal");
                break;
            }
            out_length[0]--;

            switch (in[i]) {
            case 'n': to[at] = '\n'; break;
            case 't': to[at] = '\t'; break;
            case 'v': to[at] = '\v'; break;
            case 'r': break;
            default:
                to[at] = in[i];
            }

        }
        else {
            to[at] = in[i];
        }

        i++;
        at++;
    }

    to[at] = '\0';
}

const char *Turbo_StringCopy(struct Turbo_Value *to, const char *in, const char *const end){
    if(end){}

    to->type = TJ_String;

    assert(*in=='"');
    in++;
    {
        const uint64_t length = FindQuote(in, end - in);
        uint64_t out_length = length;
        const char * const next = in + length;
        
        assert(next[-1]!='\\');
        if(next[0]!='"')
            return NULL;
        
        {
            char *n = malloc(length+1);
            encode_string(in, n, length, &out_length);

            to->value.string = n;
        }
        to->length = out_length;
        return next+1;
    }
}

const char *Turbo_String(struct Turbo_Value *to, const char *in, const char *const end){
    if(end){}

    to->type = TJ_String;

    assert(*in=='"');
    in++;
    {
        const uint64_t length = FindQuote(in, end - in);
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
