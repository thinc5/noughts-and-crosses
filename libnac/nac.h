#ifndef NOUGHTS_AND_CROSSES
#define NOUGHTS_AND_CROSSES

#include <unistd.h>
#include <stdbool.h>

typedef enum NAC_STATE {
    NAC_NONE,
    NAC_CROSS,
    NAC_NOUGHT,
    NAC_NUM_STATES
} NAC_STATE;

typedef enum NAC_MOVE_RESULT {
    NAC_MOVE_VALID,
    NAC_MOVE_INVALID
} NAC_MOVE_RESULT;

typedef enum NAC_GAME_RESULT {
    NAC_NOT_OVER,
    NAC_CROSS_WON,
    NAC_NOUGHT_WON,
    NAC_DRAWN,
    NAC_NUM_GAME_RESULTS
} NAC_GAME_RESULT;

#define NAC_DIMENSIONS 3
#define NAC_BOARD_LENGTH (NAC_DIMENSIONS*NAC_DIMENSIONS)

typedef NAC_STATE NAC_BOARD[NAC_BOARD_LENGTH];

// Reports game state.
NAC_GAME_RESULT NAC_game_status(const NAC_BOARD *board);

// If move is valid, will mutate the board.
NAC_MOVE_RESULT NAC_make_move(NAC_BOARD *board, size_t target, bool is_cross);

#endif
