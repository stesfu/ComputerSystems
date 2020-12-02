#include <stdio.h>
#include <string.h>

#include "notes.h"

// ***** IMPLEMENT ME! *****
int get_max_note_length() {
    int length = 0;
    for(int i = 0; i < NOTE_COUNT; i++) {
      if(strlen(NOTES[i]) > length){
          length = strlen(NOTES[i]);
      }
    }

    return length;
}

// ***** IMPLEMENT ME! *****
int get_max_chord_suffix_length() {
    int length = 0;
    for (int j = 0; j < CHORD_COUNT; j++){
        if(strlen(CHORD_SUFFIXES[j]) > length){
            length = strlen(CHORD_SUFFIXES[j]);
        }
    }
    return length;
}

int main(int argc, char** argv) {
    // ***** Yes, now you get to implement this too. *****
    printf("The longest NOTES string is %d characters long and the longest CHORD_SUFFIXES string is %d characters long \n", get_max_note_length(), get_max_chord_suffix_length());
    return 0;
}
