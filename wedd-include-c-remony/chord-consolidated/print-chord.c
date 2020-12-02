// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notes.h"
#include "string-plus.h"

// ***** Copy just your `main` and program-specific helper functions here (if any). *****
int main(int argc, char** argv) {
     if(argc != 3){
        puts("This program requires exactly two command line arguments: "); 
        puts("The NOTES index and the CHORD_SUFFIXES index of the note and chord suffix to print, respectively");
        return 1;
    }

    char* char_index_note = argv[1];
    char* char_index_chord = argv[2];
    char* note[1]; //improper sizes 
    char* chord[2];

    // Check that the second argument is in the correct format.
    if (!is_non_negative_numeral(char_index_note) || !is_non_negative_numeral(char_index_chord)) {
        printf("Either %s or %s is not a valid index.\n", char_index_note, char_index_chord);
        return 1;
    }

    // int string_length = strlen(string_to_split);
    int index_note = atoi(char_index_note);
    int index_chord = atoi(char_index_chord);

    // Check that the given index is within the correct range (two conditions for this---hope you can see why).
    if (index_chord < 0 || index_note < 0 || index_chord > CHORD_COUNT || index_note > NOTE_COUNT) {
        printf("Either %d or %d is out of range.\n", index_note, index_chord);
        return 1;
    }

    print_chord(index_note, index_chord);
    return 0;
}
