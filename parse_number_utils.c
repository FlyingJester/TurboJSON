#include "parse_number.h"

double s_CreateFloat(uint64_t Whole, uint64_t Decimal, uint64_t Places){
    double whole = Whole, extra = Decimal;
    extra/= 10 * Places;

    return whole + extra;

}

int ParseNumber(const char *in, double *value){
    uint64_t length;
    if(IsHex(in)){
        value[0] = HexStrToNumber(in, &length);
    }
    else{
        const uint64_t whole = DecStrToNumber(in, &length);
        if(in[length]=='.'){
            const uint64_t extra = length;
            in += length;
            in++;
            {
                const uint64_t decimal = DecStrToNumber(in, &length);
                value[0] = s_CreateFloat(whole, decimal, length);
                length+=extra;
            }
        }
        else{
            value[0] = whole;
        }
    }
    return length;
}
