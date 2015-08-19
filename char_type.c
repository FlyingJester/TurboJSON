#include "parse_number.h"

unsigned HexDigitValue(char c){
    if(c<='9') return c-'0';
    if(c<='F') return c-'A';
    return c-'a';
}

int IsDecDigit(char c){
    return c>='0' && c<='9';
}

int IsHexDigit(char c){
    return IsDecDigit(c) || (c>='A' && c<='F') || (c>='a' && c<='f');
}

int IsOctDigit(char c){
    return c>='0' && c<'8';
}

int IsBinDigit(char c){
    return c=='0' || c=='1';
}
