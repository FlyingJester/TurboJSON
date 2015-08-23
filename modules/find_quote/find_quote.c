#include "find_quote.h"

uint64_t FindQuote(const char *in){
    unsigned i = 0;
    while((*in != '\0') && (*in != '"')){
        in++;
        i++;
    }
    return i;
}

int CompareStrings(const char *in, const char *to, uint64_t to_length){
    while(to_length--){
        if((*in)!=(*to))
            return 0;
        to++;
        in++;
    }
    return 1;
}
