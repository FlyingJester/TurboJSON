#include "number_literal.h"
#include <math.h>

#define N_POW_TEN 64

/*
static const double pow_of_ten[N_POW_TEN] = {
     10e0, 10e1,  10e2,  10e3,  10e4,  10e5,  10e6,  10e7,  10e8,
     10e9,  10e10, 10e11, 10e12, 10e13, 10e14, 10e15, 10e16,
     10e17, 10e18, 10e19, 10e20, 10e21, 10e22, 10e23, 10e24,
     10e25, 10e26, 10e27, 10e28, 10e29, 10e30, 10e31, 10e32,
     10e33, 10e34, 10e35, 10e36, 10e37, 10e38, 10e39, 10e40,
     10e41, 10e42, 10e43, 10e44, 10e45, 10e46, 10e47, 10e48,
     10e49, 10e50, 10e51, 10e52, 10e53, 10e54, 10e55, 10e56,
     10e57, 10e58, 10e59, 10e60, 10e61, 10e62, 10e63, 10e64
};
*/
double NumberLiteral(const char **in){
    const char *at = *in;
    long whole = 0, decimal = 0, places = 0;
    double exponent = 1.0;
    
    if(*at=='-')
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

    if(**in == '-'){
        whole = -whole;
    }
    
    in[0] = at;
    {
        if(*at=='.'){
            at++;
            while((*at >= '0') && (*at <= '9')){
                decimal *= 10;
                decimal += (*at)-'0';
                places++;
                at++;
            }
        }
        else if ((*at!='e') && (*at!='E')){
            in[0] = at;
            return whole;
        }

        if((*at=='e') || (*at=='E')){
            unsigned exponent_accum = 0, exponent_is_negative = 0;
            
            at++;
            if(*at=='-'){
                exponent_is_negative = 1;
                at++;
            }
            
            while((*at >= '0') && (*at <= '9')){
                exponent_accum *= 10;
                exponent_accum += (*at)-'0';
                at++;
            }
            
            while(exponent_accum--){
                exponent*=10.0;
            }
            if(exponent_is_negative)
                exponent=1.0/exponent;
            
        }

        {
            double fraction = decimal;
            double that = whole;
            while(places--)
                fraction/=10.0;
            
            in[0] = at;
            
            return (that + fraction) * exponent;
        }
    }
}
