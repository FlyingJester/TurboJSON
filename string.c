unsigned find_quote(const char *in, unsigned length){
    unsigned i = 0;
    while(*in!='"' && i++ < length)
        in++;
    return i;
}
