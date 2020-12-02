#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io-utilities.h"
#include "string-plus.h"
#include "mine-c-weeper.h"

#define DEFAULT_PROBABILITY 10
#define MAX_COMMAND_LENGTH 1024
// MAX_COMMAND_LENGTH is way more than we need but we err on the side of caution.

// Helper functions for determining what kind of arguments we got.
bool dimension_args(int argc, char** argv) {
    return argc == 3 && is_non_negative_numeral(argv[1]) && is_non_negative_numeral(argv[2]);
}

bool dimension_and_probability_args(int argc, char** argv) {
    return argc == 4 && is_non_negative_numeral(argv[1]) && is_non_negative_numeral(argv[2]) &&
        is_non_negative_numeral(argv[3]);
}

bool file_args(int argc, char** argv) {
    return argc == 2;
}

/**
 * Creates a game based on the given arguments. If the arguments are invalid, NULL is returned.
 */
mcw_game* create_game_based_on_args(int argc, char** argv) {
    // Check arguments to figure out how to initialize the game.
    if (dimension_args(argc, argv) || dimension_and_probability_args(argc, argv)) {
        // We already checked for numerals so we can convert right away.
        int width = atoi(argv[1]);
        int height = atoi(argv[2]);
        int probability = dimension_and_probability_args(argc, argv) ? atoi(argv[3]) : DEFAULT_PROBABILITY;

        if (width < 1 || height < 1) {
            puts("Sorry, but zero dimensions are not allowed.");
            puts("");
            return NULL;
        }

        return initialize_random_game(width, height, probability);
    } else if (file_args(argc, argv)) {
        mcw_game* game = initialize_file_game(argv[1]);
        if (game == NULL) {
            puts("Sorry, but something appears to be amiss with the game file.");
            puts("");
        }

        return game;
    } else {
        return NULL;
    }
}

void display_help() {
    puts("You have the following command choices:");
    puts("- 'o <x> <y>' will open a square");
    puts("- 'm <x> <y>' will mark a square");
    puts("- 'h' will display this help listing");
    puts("- 'n' will start a new game");
    puts("- 'q' will quit");
}

typedef enum {
    command_handled,
    command_new,
    command_unrecognized,
    command_quit
} command_result;

command_result process_command(char* command_string, mcw_game* game) {
    char command;
    int x;
    int y;

    // As before, the use of `sscanf` is a little above our level, so it is written for you here.
    int successful_scans = sscanf(command_string, "%c %d %d", &command, &x, &y);
    if (successful_scans == 1) {
        if (command == 'h') {
            display_help();
            return command_handled;
        }

        if (command == 'n' || command == 'q') {
            // If the player quits or starts over, we display the full board.
            puts("\nGame over! Here is the entire field:\n");
            show_all(game);
            display_game_state(game);

            if (command == 'n') {
                return command_new;
            }

            if (command == 'q') {
                return command_quit;
            }
        }
    } else if (successful_scans == 3) {
        // Range check.
        if (!is_in_game_bounds(game, x, y)) {
            printf("Sorry, but either x=%d or y=%d is out of range.\n", x, y);
            return command_handled;
        }

        if (command == 'm') {
            mark_game_square(game, x, y);
            return command_handled;
        }

        if (command == 'o') {
            reveal_game_square(game, x, y);
            return command_handled;
        }
    }

    // If we get here, we didn’t know what to do with the command.
    return command_unrecognized;
}

int main(int argc, char** argv) {
    // Don’t worry about the srandom() call---but don’t change or remove it either!
    // It’s related to random number generation.
    srandom(time(NULL));

    mcw_game* game = create_game_based_on_args(argc, argv);
    if (game == NULL) {
        emit_utf_8(MARKER);
        printf(" Welcome to Mine-C-Weeper! ");
        emit_utf_8(WEEPER);
        puts("");

        puts("Usage: mine-c-weeper <width> <height> [<weeper frequency>]");
        puts("   or: mine-c-weeper <filename>");
        puts("");
        puts("The weeper frequency is the chance that a given square is a weeper.");
        printf("The default weeper frequency is %d (i.e., %d%%).\n", DEFAULT_PROBABILITY, DEFAULT_PROBABILITY);
        puts("");
        puts("Caution: File error-checking is minimal, so if the map file is in the wrong format,");
        puts("         this program may just terminate without warning.");
        return 1;
    }

    bool done = false;
    display_help();
    while (!done) {
        puts("");

        int weeper_count = get_weeper_count(game);
        int flag_count = get_flag_count(game);
        printf("There are %d weeper%s here.\n", weeper_count, weeper_count == 1 ? "" : "s");
        printf("You have planted %d flag%s.\n", flag_count, flag_count == 1 ? "" : "s");
        puts("");
        display_game_state(game);
        puts("");
        puts("What would you like to do? (enter 'h' for help)");

        char command_string[MAX_COMMAND_LENGTH];
        fgets(command_string, MAX_COMMAND_LENGTH, stdin);
        command_result result = process_command(command_string, game);

        // Future languages note: C is one of the few languages where `switch` is a viable alternative.
        // In most other languages, there are better approaches than `switch`.
        switch (result) {
            case command_handled:
                // All good, nothing further to do.
                break;

            case command_new:
                free_game(game);
                game = create_game_based_on_args(argc, argv);
                puts("\nOK, starting over!");
                break;

            case command_unrecognized:
                puts("\nSorry, that command was not recognized.");
                break;

            case command_quit:
                puts("\nThank you for playing Mine-C-Weeper!");
                done = true;
                break;
        }

        if (!done) {
            bool player_lost = is_game_over_loss(game);
            bool player_won = is_game_over_win(game);
            if (player_lost || player_won) {
                char* message = player_lost ?
                    "Sorry, you have revealed a weeper!" :
                    "Congratulations! You have cleared the field.";

                printf("\n%s Thank you for playing.\n\n", message);
                display_game_state(game);
                puts("");
                puts("Here is the whole field, revealed!");
                puts("");
                show_all(game);
                display_game_state(game);
                puts("");
                done = true;
            }
        }
    }

    free_game(game);
    return 0;
}
