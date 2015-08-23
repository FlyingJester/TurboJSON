#include "error.h"
#include <string.h>
#include <stdlib.h>

const char *Turbo_Error(struct Turbo_Value *to, const char *in, const char * message){
    const unsigned msg_len = (message)?strlen(message):0;
    char *msg = malloc(msg_len+1);

    to->type = TJ_Error;

    msg[msg_len] = '\0';
    if(msg_len){
        memcpy(msg, message, msg_len);
    }

    to->value.error.message = msg;
    to->value.error.at = in;
    to->value.error.str = NULL;
    
    fprintf(stderr, "Error: %s (was %c)\n", message, *in);
    
    return NULL;
}

void Turbo_WriteError(struct Turbo_Value *that, FILE *out, int level){
    const char *z = that->value.error.at;
    unsigned newline = 0;
    do{
        z = strchr(z, '\n');
        newline++;
    }while(z<that->value.error.str);
    fprintf(out, "%i > Error on line %i: %s \t(was %c)\n", level, newline, that->value.error.message, *that->value.error.at);
}

