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
    
    fprintf(stderr, "Error: %s (was %c)\n", message, *in);
    
    return NULL;
}

void Turbo_WriteError(struct Turbo_Value *that, FILE *out, int level){
    fprintf(out, "%i > Error: %s \t(was %c)\n", level, that->value.error.message, *that->value.error.at);
}

