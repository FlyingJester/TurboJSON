#include "string.h"

uint64_t find_quote(const char *in, unsigned length){
    unsigned i = 0;
    while(*in!='"' && i++ < length)
        in++;
    return i;
}

uint64_t compare_strings(const char *in, const char *to, uint64_t to_length){
    while(to_length--){
        if((*in)!=(*to))
            return 0;
        to++;
        in++;
    }
    return 1;
}
