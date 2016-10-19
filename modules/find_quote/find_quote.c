#include "find_quote.h"

uint64_t FindQuote(const char *in, unsigned long length){
    unsigned i = 0;
    while(i < length && (*in != '\0') && (*in != '"')){
        in++;
        i++;

        if (in[0] == '\\' && in[1] == '"') {
            in+=2;
            i+=2;
        }

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
