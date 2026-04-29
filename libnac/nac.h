#ifndef NOUGHTS_AND_CROSSES
#define NOUGHTS_AND_CROSSES

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

typedef enum NAC_GLYPH {
    NAC_NONE,
    NAC_CROSS,
    NAC_NOUGHT,
    NAC_NUM_STATES
} NAC_GLYPH;

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

typedef uint8_t NAC_DIMENSIONS;

typedef uint16_t NAC_STATE_RANGE;

typedef struct
{
    NAC_DIMENSIONS dimensions;
    NAC_STATE_RANGE length;
    NAC_GLYPH *board;
} NAC_STATE;

// Reports game state.
NAC_GAME_RESULT NAC_game_status(const NAC_STATE *state);

// If move is valid, will mutate the board.
NAC_MOVE_RESULT NAC_make_move(NAC_STATE *state, NAC_STATE_RANGE target, NAC_GLYPH glyph);

#endif
