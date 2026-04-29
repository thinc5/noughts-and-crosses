#ifndef CLI_DISPLAY_H
#define CLI_DISPLAY_H

#include <stdbool.h>
#include <nac.h>

void display_game(const NAC_STATE *state);
void display_game_result(NAC_GAME_RESULT result);
void display_prompt(bool cross_turn);

#endif
