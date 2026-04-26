#include "nac.h"

#include <stdio.h>

// If we were ever to have a winning sequence not equal the
// dimensions of the square, this could change (UNLIKELY).
#define WINNING_SEQUENCE NAC_DIMENSIONS

bool winning_total(size_t total) {
    return (total == (NAC_CROSS * NAC_CROSS * NAC_CROSS) ||
        total == (NAC_NOUGHT * NAC_NOUGHT * NAC_NOUGHT));
}

bool check_diagonal(const NAC_BOARD *board, size_t start) {
    size_t left_total = 1;
    size_t right_total = 1;
    for (size_t i = 0; i < WINNING_SEQUENCE; i++) {
        // E.g. 1,1 (0) -> 2,2 (4) -> 3,3 (8)
        size_t left_index = (start + i) + (NAC_DIMENSIONS * (i + start));
        // E.g. 3,1 (2) -> 2,2 (4) -> 1,3 (6)
        size_t right_index = (WINNING_SEQUENCE - i - 1 + start) + (NAC_DIMENSIONS * (i + start));
        if (left_index >= NAC_BOARD_LENGTH || right_index >= NAC_BOARD_LENGTH) {
            return NAC_NONE;
        }

        left_total *= (*board)[left_index];
        right_total *= (*board)[right_index];
    }

    if (winning_total(left_total)) {
        return (*board)[(start) + (NAC_DIMENSIONS * start)];
    }

    if (winning_total(right_total)) {
        return (*board)[(NAC_DIMENSIONS - 1 + start) + (NAC_DIMENSIONS * start)];
    }

    return NAC_NONE;
}

NAC_STATE check_horizontal(const NAC_BOARD *board, size_t start) {
    size_t total = 1;
    for (size_t i = 0; i < WINNING_SEQUENCE; i++) {
        total *= (*board)[start + i];
    }

    if (winning_total(total)) {
        return (*board)[start];
    }

    return NAC_NONE;
}

NAC_STATE check_vertical(const NAC_BOARD *board, size_t start) {
    size_t total = 1;
    for (size_t i = 0; i < WINNING_SEQUENCE; i++) {
        total *= (*board)[start + (NAC_DIMENSIONS * i)];
    }

    if (winning_total(total)) {
        return (*board)[start];
    }

    return NAC_NONE;
}

NAC_GAME_RESULT NAC_game_status(const NAC_BOARD *board) {
    NAC_STATE winning = NAC_NONE;
    bool full = true;

    for (size_t i = 0; i < NAC_DIMENSIONS; i++) {
        // Horizontal inspection.
        if ((winning = check_horizontal(board, i * NAC_DIMENSIONS)) != NAC_NONE) {
            break;
        }
        
        // Vertical inspection.
        if ((winning = check_vertical(board, i)) != NAC_NONE) {
            break;
        }

        // Diagonal inspection. 
        if ((winning = check_diagonal(board, i)) != NAC_NONE) {
            break;
        }

        // Encountered a zero? (we check horizontally)
        if (full) {
            for (size_t j = i * NAC_DIMENSIONS; j < NAC_DIMENSIONS; j++) {
                if ((*board)[j] == NAC_NONE) {
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

NAC_MOVE_RESULT NAC_make_move(NAC_BOARD *board, size_t target, bool is_cross) {
    NAC_STATE *cell = &(*board)[target];
    if (*cell != NAC_NONE) {
        return NAC_MOVE_INVALID;
    }

    *cell = is_cross ? NAC_CROSS : NAC_NOUGHT;
    return NAC_MOVE_VALID;
}
