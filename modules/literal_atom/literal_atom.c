#include "literal_atom.h"

int TrueAtom(const char *in){
    return (in[0] == 't' &&
    in[1] == 'r' &&
    in[2] == 'u' &&
    in[3] == 'e');
}

int FalseAtom(const char *in){
    return (in[0] == 'f' &&
    in[1] == 'a' &&
    in[2] == 'l' &&
    in[3] == 's' &&
    in[4] == 'e');
}

int NullAtom(const char *in){
    return (in[0] == 'n' &&
    in[1] == 'u' &&
    in[2] == 'l' &&
    in[3] == 'l');
}
