#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <nac.h>

#include "cli/input.h"
#include "cli/display.h"


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

            if (!parse_move(buffer, &target_index)) {
                printf("Bad input, try again\n");
                continue;
            }

        } while ((move_result = NAC_make_move(&board, target_index, cross_turn)) == NAC_MOVE_INVALID);

        cross_turn = !cross_turn;
    } while ((game_result = NAC_game_status((const NAC_BOARD *) &board)) == NAC_NOT_OVER);

    display_game((const NAC_BOARD *) &board);
    display_game_result(game_result);
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
