#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "notes.h"

#define MAX_SUBSTRING 15
#define INVALID -1

// ***** IMPLEMENT ME! *****
// ***** Feel free to add more functions if you think they will make it easier to implement split_note_and_chord.
int get_string_index(char* string, char* note) {
    for(int i = 0; i < strlen(string); i++){
        if(strcmp(string, note) == 0){
            return i;
        }
    }
    return INVALID;
}

int get_note_index(char* string) {
    for(int i = 0; i < NOTE_COUNT; i++){
        if(strcmp(NOTES[i], string) == 0){
            return i;
        }
    }
    return INVALID;
}

int get_max_note_length(){
    int length = 0;
    for(int i = 0; i < NOTE_COUNT; i++) {
        if(strlen(NOTES[i]) > length){
            length = strlen(NOTES[i]);
        }
    }
    return length;
}

void split_string_at_index(char* string, int index, char* left, char* right) {
    for(int i = 0 ; i < index; i++){
        left[i] = string[i];
    } 

    left[index] = '\0';

    for(int j = index; j < strlen(string); j++){
       right[j - index] = string[j];
    }

    right[strlen(string) - index] = '\0';
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
