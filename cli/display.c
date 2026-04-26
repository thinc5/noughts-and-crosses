#include "display.h"

#include <stdio.h>

static const char NAC_SYMBOLS[NAC_NUM_STATES] = { '_', 'X', 'O' };

static const char* GAME_RESULT_MESSAGES[NAC_NUM_GAME_RESULTS] = {
    [NAC_NOT_OVER] = "Game not over.",
    [NAC_CROSS_WON] = "Cross player won!",
    [NAC_NOUGHT_WON] = "Nought player won!",
    [NAC_DRAWN] = "Game ended in a draw."
};

void display_game(const NAC_BOARD *board) {
    for (size_t i = 0; i < NAC_BOARD_LENGTH; i++) {
        printf("%c", NAC_SYMBOLS[(*board)[i]]);

        if ((i % NAC_DIMENSIONS) == NAC_DIMENSIONS - 1) {
            printf("\n");
        }
    }
}

void display_game_result(NAC_GAME_RESULT result) {
    printf("%s\n", GAME_RESULT_MESSAGES[result]);
}

void display_prompt(bool cross_turn) {
    printf(
        "%s's turn, enter coordinates \"x,y\" > ",
        cross_turn ? "Cross" : "Nought"
    );
}
