unsigned SkipWhitespace(const char *in, unsigned length){
    unsigned i = 0;
    while((*in==' ' || *in=='\t' || *in=='\n') && i++ < length)
        in++;
    return i;
}
