// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdio.h>
#include <string.h>

#include "notes.h"

#define MAX_SUBSTRING 15

// ***** Copy just your `main` and program-specific helper functions here (if any). *****
int main(int argc, char** argv) {
    if(argc != 2){
        puts("This program requires exactly one command line argument.");
        return 1;
    }

    char* string_to_split = argv[1];
    char note[MAX_SUBSTRING + 1];
    char chord[MAX_SUBSTRING + 1];

    if(split_note_and_chord(string_to_split, note, chord) == 0){
       split_note_and_chord(string_to_split, note, chord); 
       printf("[%s] [%s] \n", note, chord); 
       return 0;
    }else if(split_note_and_chord(string_to_split, note, chord) == 1){
       split_note_and_chord(string_to_split, note, chord); 
       printf("[%s] [] \n", note);
       return 0;
    }else{
       printf("%s is not a valid chord \n", string_to_split);
        return 1;  
    }

    return 0;
}
