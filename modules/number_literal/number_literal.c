#include "number_literal.h"
#include <math.h>

double NumberLiteral(const char **in){
    const char *at = *in;
    long whole = 0, decimal = 0, places = 0;
    if(**in=='-')
        at++;
    
    if(*at!='0'){
        while((*at >= '0') && (*at <= '9')){
            whole *= 10;
            whole += (*at)-'0';
            at++;
        }
    }
    else{
        at++;
    }

    if(*at=='.'){
        at++;
        while((*at >= '0') && (*at <= '9')){
            decimal *= 10;
            decimal += (*at)-'0';
            places++;
            at++;
        }
    }
    {
        double divider = 1;
        while(places--)
            divider *= 10.0;
        
/*        double divider = pow(10, places); */
        double fraction = decimal;
        double that = whole;
        
        fraction /= divider;
        
        if(**in == '-')
            fraction = -fraction;
        
        *in = at;
        
        return that + fraction;
    }
}
