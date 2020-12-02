#include <stdbool.h>
#include <stdio.h>
#include <string.h>  // In case your implementation needs it. It does not have to.

#include "string-plus.h"
#include "notes.h"

char *NOTES[] = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};
int NOTE_COUNT = sizeof(NOTES) / sizeof(char*);

// C has more sophisticated ways to express these structures, but at our level we
// stay with multiple arrays that have coordinated index values (i.e., the same
// index on these arrays corresopnds to the same type of chord).
char *CHORD_SUFFIXES[] = {
    "",     // major
    "m",    // minor
    "7",    // dominant 7th
    "M7",   // major 7th
    "m7",   // minor 7th
    "dim7"  // diminished 7th
};

int CHORD_COUNT = sizeof(CHORD_SUFFIXES) / sizeof(char*);

// C needs to know the maximum size of the inner array, but not the outer one 🤷🏽‍♂️
int CHORD_STEPS[][3] = {
    {4, 3},     // major
    {3, 4},     // minor
    {4, 3, 3},  // dominant 7th
    {4, 3, 4},  // major 7th
    {3, 4, 3},  // minor 7th
    {3, 3, 3}   // diminished 7th
};

// Yes, there are ways of computing this dynamically but for now we choose to list
// them explicitly to show how these arrays correspond to each other.
int CHORD_STEP_COUNT[] = {
    2,  // major
    2,  // minor
    3,  // dominant 7th
    3,  // major 7th
    3,  // minor 7th
    3   // diminished 7th
};

// ***** MOVE YOUR IMPLEMENTATIONS HERE! *****
int get_max_note_length() {
    int length = 0;
    for(int i = 0; i < NOTE_COUNT; i++) {
      if(strlen(NOTES[i]) > length){
          length = strlen(NOTES[i]);
      }
    }

    return length;
}

int get_max_chord_suffix_length() {
    int length = 0;
    for (int j = 0; j < CHORD_COUNT; j++){
        if(strlen(CHORD_SUFFIXES[j]) > length){
            length = strlen(CHORD_SUFFIXES[j]);
        }
    }
    return length;
}

int get_note_index(char* string) {
    for(int i = 0; i < NOTE_COUNT; i++){
        if(strcmp(NOTES[i], string) == 0){
            return i;
        }
    }
    return INVALID;
}

int get_chord_index(char* string) {
    for(int i = 0; i < CHORD_COUNT; i++){
        if(strcmp(CHORD_SUFFIXES[i], string) == 0){
            return i;
        }
    }
    return INVALID;
}

int note_exists(char* string, char* note, char* chord){
   for(int i = get_max_note_length(); i > -1; i --){
       split_string_at_index(string, i, note, chord);
        if(get_note_index(note) > -1){
            return get_note_index(note);
        }
    } 
    return INVALID;  
}

int chord_exists(char* chord){
   for(int i = 0; i < CHORD_COUNT; i ++){
        if(strcmp(CHORD_SUFFIXES[i], chord) == 0){
            return 0;
        }
    } 
    return INVALID;  
}

int get_string_index(char* string, char* note) {
    for(int i = 0; i < strlen(string); i++){
        if(strcmp(string, note) == 0){
            return i;
        }
    }
    return INVALID;
}

int split_note_and_chord(char* string, char* note, char* chord) {
    if(get_note_index(string) > -1){
        strcpy(note,string);
        return 1;
    }else{
        if(note_exists(string, note, chord) > -1 && chord_exists(chord) > -1){
            split_string_at_index(string, get_string_index(string, note), note, chord); 
            return 0; 
        }
        return INVALID; 
    }
}

void print_chord(int note_index, int chord_index) {
    char chords[CHORD_STEP_COUNT[chord_index] + 1]; 
    chords[0] = '\0'; 
    int index;
    index = note_index; 
    strcat(chords, NOTES[note_index]);
 
    for(int i = 0; i < CHORD_STEP_COUNT[chord_index]; i++){
        index = (index + CHORD_STEPS[chord_index][i]) % NOTE_COUNT; 
        strcat(chords, " ");
        strcat(chords, NOTES[index]);
    }
   
    printf("%s%s: %s \n", NOTES[note_index],CHORD_SUFFIXES[chord_index], chords);
}
