#include "nac.h"

bool winning_total(size_t total) {
    return (total == (NAC_CROSS * NAC_CROSS * NAC_CROSS) ||
        total == (NAC_NOUGHT * NAC_NOUGHT * NAC_NOUGHT));
}

bool check_diagonal(const NAC_STATE *state, NAC_STATE_RANGE start) {
    size_t left_total = 1;
    size_t right_total = 1;
    for (NAC_STATE_RANGE i = 0; i < state->dimensions; i++) {
        // E.g. 1,1 (0) -> 2,2 (4) -> 3,3 (8)
        NAC_STATE_RANGE left_index = (start + i) + (state->dimensions * (i + start));
        // E.g. 3,1 (2) -> 2,2 (4) -> 1,3 (6)
        NAC_STATE_RANGE right_index = (state->dimensions - i - 1 + start) + (state->dimensions * (i + start));
        if (left_index >= state->length || right_index >= state->length) {
            return NAC_NONE;
        }

        left_total *= state->board[left_index];
        right_total *= state->board[right_index];
    }

    if (winning_total(left_total)) {
        return state->board[(start) + (state->dimensions * start)];
    }

    if (winning_total(right_total)) {
        return state->board[(state->dimensions - 1 + start) + (state->dimensions * start)];
    }

    return NAC_NONE;
}

NAC_GLYPH check_horizontal(const NAC_STATE *state, NAC_STATE_RANGE start) {
    size_t total = 1;
    for (NAC_STATE_RANGE i = 0; i < state->dimensions; i++) {
        total *= state->board[start + i];
    }

    if (winning_total(total)) {
        return state->board[start];
    }

    return NAC_NONE;
}

NAC_GLYPH check_vertical(const NAC_STATE *state, NAC_STATE_RANGE start) {
    size_t total = 1;
    for (NAC_STATE_RANGE i = 0; i < state->dimensions; i++) {
        total *= state->board[start + (state->dimensions * i)];
    }

    if (winning_total(total)) {
        return state->board[start];
    }

    return NAC_NONE;
}

NAC_GAME_RESULT NAC_game_status(const NAC_STATE *state) {
    NAC_GLYPH winning = NAC_NONE;
    bool full = true;

    for (NAC_STATE_RANGE i = 0; i < state->dimensions; i++) {
        // Horizontal inspection.
        if ((winning = check_horizontal(state, i * state->dimensions)) != NAC_NONE) {
            break;
        }
        
        // Vertical inspection.
        if ((winning = check_vertical(state, i)) != NAC_NONE) {
            break;
        }

        // Diagonal inspection. 
        if ((winning = check_diagonal(state, i)) != NAC_NONE) {
            break;
        }

        // Encountered a zero? (we check horizontally)
        if (full) {
            for (NAC_STATE_RANGE j = i * state->dimensions; j < state->dimensions; j++) {
                if (state->board[j] == NAC_NONE) {
                    full = false;
                    break;
                }
            }
        }
    }

    // First case; someone won. 
    switch (winning)
    {
    case NAC_CROSS:
        return NAC_CROSS_WON;
    case NAC_NOUGHT:
        return NAC_NOUGHT_WON;
    default:
        break;
    }

    // Second case; board is full and someone did not win.
    if (full) {
        return NAC_DRAWN;
    }

    // Last case, game can be continued.
    return NAC_NOT_OVER;
}

NAC_MOVE_RESULT NAC_make_move(NAC_STATE *state, NAC_STATE_RANGE target, NAC_GLYPH glyph) {
    NAC_GLYPH *cell = &(state->board[target]);
    if (*cell != NAC_NONE) {
        return NAC_MOVE_INVALID;
    }

    *cell = glyph;
    return NAC_MOVE_VALID;
}
