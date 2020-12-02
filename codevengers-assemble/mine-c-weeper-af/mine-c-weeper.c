#include <stdio.h>
#include <stdlib.h>

#include "io-utilities.h"
#include "mine-c-weeper.h"

#define BUFFER_SIZE 1024
#define MAX_PROBABILITY 100

#define OPEN_CHAR '.'
#define WEEPER_CHAR 'W'

// ***** IMPLEMENTATION NOTE: Copy your entire mine-c-weeper implementation here
//                            _except_ for `is_in_game_bounds` because that should
//                            now go in _is-in-game-bounds.asm_.

mcw_game* alloc_game(int width, int height) {
    return NULL;
}

void free_game(mcw_game* game) {
}

void show_all(mcw_game* game) {
}

void hide_all(mcw_game* game) {
}

mcw_game* initialize_random_game(int width, int height, int probability) {
    mcw_game* game = alloc_game(width, height);
    if (game == NULL) {
        return NULL;
    }

    int threshold = probability > MAX_PROBABILITY ? MAX_PROBABILITY : probability;

    int x, y;
    for (y = 0; y < game->height; y++) {
        for (x = 0; x < game->width; x++) {
            int mine_roll = random() % MAX_PROBABILITY;
            game->field[y][x] = mine_roll < threshold ? weeper : open;
        }
    }

    hide_all(game);
    return game;
}

mcw_game* initialize_file_game(char* filename) {
    FILE* game_file = fopen(filename, "r");
    if (!game_file) {
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    mcw_game* game = NULL;
    int y = 0;
    while (!feof(game_file)) {
        fgets(buffer, BUFFER_SIZE, game_file);
        if (game == NULL) {
            int width;
            int height;
            int successful_scans = sscanf(buffer, "%d %d", &width, &height);
            if (successful_scans < 2) {
                fclose(game_file);
                return NULL;
            } else {
                game = alloc_game(width, height);
                if (game == NULL) {
                    fclose(game_file);
                    return NULL;
                }
            }
        } else {
            if (y >= game->height) {
                break;
            }

            int x;
            for (x = 0; x < game->width; x++) {
                if (buffer[x] == OPEN_CHAR || buffer[x] == WEEPER_CHAR) {
                    game->field[y][x] = buffer[x] == OPEN_CHAR ? open : weeper;
                } else {
                    fclose(game_file);
                    return NULL;
                }
            }

            y++;
        }
    }

    fclose(game_file);
    hide_all(game);
    return game;
}

void display_game_field(mcw_game* game) {
}

int get_weeper_count(mcw_game* game) {
    return 0;
}

int get_flag_count(mcw_game* game) {
    return 0;
}

int get_adjacent_weeper_count(mcw_game* game, int x, int y) {
    return 0;
}

void display_game_state(mcw_game* game) {
}

// ***** Re-reminder: Do _not_ put `is_in_game_bounds` here. That belongs in
//                    _is-in-game-bounds.asm_, written in assembly language.

void mark_game_square(mcw_game* game, int x, int y) {
}

void reveal_game_square(mcw_game* game, int x, int y) {
}

bool is_game_over_loss(mcw_game* game) {
    return false;
}

bool is_game_over_win(mcw_game* game) {
    return true;
}
