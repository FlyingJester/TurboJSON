#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "parse.h"

int main(int argc, char *argv[]){
    struct stat buf;
    FILE *file;
    char *buffer, *filename;
    
    if(argc<2){
        puts("Missing file name");
        puts("Usage: test [input_file_name] [-p output_file_name]");
        puts("\t-p writes a new copy of the JSON data (to verify an accurate parse tree was generated).");
        puts("\tOtherwise the file is parsed 1000 times for benchmarking purposes.");
        return EXIT_SUCCESS;
    }
    else{
        filename = argv[1];
    }
    
    stat(filename, &buf);
    
    file = fopen(filename, "r");

    if(!file){
        puts("Cannot open file");
        return EXIT_FAILURE;
    }
    
    buffer = malloc(buf.st_size + 1);
    buffer[buf.st_size] = 0;
    
    if(!fread(buffer, 1, buf.st_size, file)){
        return 1;
    }
    
    if(argc>2 && strcmp(argv[2], "-p")==0){
        struct Turbo_Value root;
        const char *last = buffer + buf.st_size;
        Turbo_Parse(&root, buffer, last);
        Turbo_WriteValue(&root, stdout, 0);
    }
    else{
        int i = 1000;
        struct Turbo_Value root;
        const char *last = buffer + buf.st_size;
        while(i--){
            Turbo_Parse(&root, buffer, last);
            TurboFree(&root);
        }

/*        Turbo_WriteValue(&root, stdout, 0);
*/        
    }
    fclose(file);
    return 0;
}
