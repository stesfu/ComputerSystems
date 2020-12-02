#include <stdio.h>
#include <string.h>

#include "notes.h"

#define INVALID -1

// ***** IMPLEMENT ME! *****
int get_chord_index(char* string) {
    for(int i = 0; i < CHORD_COUNT; i++){
        if(strcmp(CHORD_SUFFIXES[i], string) == 0){
            return i;
        }
    }
    return INVALID;
}

int main(int argc, char** argv) {
    if(argc != 2){
        puts("This program requires exactly one command line argument.");
        return 1; 
    }

    if(get_chord_index(argv[1]) > -1){
        printf("%s is at CHORD_SUFFIXES index %d. \n", argv[1], get_chord_index(argv[1]));
    }else{
        printf("%s is not a valid chord. \n", argv[1]);
    }
    return 0;
}
