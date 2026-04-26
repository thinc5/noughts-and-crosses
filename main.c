#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "noughts_and_crosses.h"

static const char NAC_SYMBOLS[NAC_NUM_STATES] = { '_', 'X', 'O' };

static const char* GAME_RESULT_MESSAGES[NAC_NUM_GAME_RESULTS] = {
    [NAC_NOT_OVER] = "Game not over.",
    [NAC_CROSS_WON] = "Cross player won!",
    [NAC_NOUGHT_WON] = "Nought player won!",
    [NAC_DRAWN] = "Game ended in a draw."
};

void display_game_result(NAC_GAME_RESULT result) {
    printf("%s\n", GAME_RESULT_MESSAGES[result]);
}

void display_game(const NAC_BOARD *board) {
    for (size_t i = 0; i < NAC_BOARD_LENGTH; i++) {
        printf("%c", NAC_SYMBOLS[(*board)[i]]);

        if ((i % NAC_DIMENSIONS) == NAC_DIMENSIONS - 1) {
            printf("\n");
        }
    }
}

void display_prompt(bool cross_turn) {
    printf(
        "%s's turn, enter coordinates \"x,y\" > ",
        cross_turn ? "Cross" : "Nought"
    );
}

bool parse_input(char *buffer, size_t *target) {
    char *x_str = strtok(buffer, ",");
    char *y_str = strtok(NULL, ",");
    if (x_str == NULL || y_str == NULL){
        return false;
    }

    int x = atoi(x_str);
    int y = atoi(y_str);
    if (x < 1 || x > 3 || y < 1 || y > 3) {
        return false;
    }

    *target = (size_t) (x - 1) + ((y - 1) * NAC_DIMENSIONS);

    return true;
}

bool poll_input(char **buffer) {
    #define INPUT_BUFFER_SIZE 30
    static char INPUT_BUFFER[INPUT_BUFFER_SIZE] = { '\0' };
    memset(INPUT_BUFFER, '\0', INPUT_BUFFER_SIZE);
    
    *buffer = INPUT_BUFFER;

    size_t position = 0;
    char last_read = '\0';
    while ((last_read = getchar()) != EOF)
    {
        switch (last_read) {
            case '\b':
                if (position > 1) {
                    INPUT_BUFFER[position] = '\0';
                    position--;
                }
                break;
            case '\n':
                if (position > 0) {
                    return true;
                }
                break;
            default:
                if (position + 1 < INPUT_BUFFER_SIZE) {
                    INPUT_BUFFER[position] = last_read;
                    position++;
                }
                break;
        }
    }
    return false;
}

void play_game() {
    char *buffer = NULL;
    bool cross_turn = true;
    NAC_BOARD board = { NAC_NONE };
    NAC_GAME_RESULT game_result = NAC_NOT_OVER;
    NAC_MOVE_RESULT move_result = NAC_MOVE_INVALID;
    size_t target_index = 0;

    do {
        display_game((const NAC_BOARD *) &board);

        do {
            display_prompt(cross_turn);
            if (!poll_input(&buffer)) {
                continue;
            }

            if (!parse_input(buffer, &target_index)) {
                printf("Bad input, try again\n");
                continue;
            }

        } while ((move_result = NAC_make_move(&board, target_index, cross_turn)) == NAC_MOVE_INVALID);

        cross_turn = !cross_turn;
    } while ((game_result = NAC_game_status((const NAC_BOARD *) &board)) == NAC_NOT_OVER);

    display_game((const NAC_BOARD *) &board);
    display_game_result(game_result);
}

char parse_yn(char *buffer) {
    if (strlen(buffer) != 1) {
        return '\0';
    }

    char ans = buffer[0];
    if (ans == 'y' || ans == 'Y') {
        return 'y';
    }

    if (ans == 'n' || ans == 'N') {
        return 'n';
    }

    return '\0';
}

int main() {
    char *answer_buffer = NULL;
    bool exit = false;

    do {
        play_game();

        bool answered = false;
        do {
            printf("Play again? \"y/n\" > ");
            if (!poll_input(&answer_buffer)) {
                continue;
            }
            char result = parse_yn(answer_buffer);
            switch (result) {
                case 'n':
                    exit = true;
                case 'y':
                    answered = true;
                break;
                default:
                    printf("Invalid answer, please try again.\n");
            }
        } while (!answered);

    } while (!exit);

    return 0;
}
