// evaluation.c
// Licensed under the MIT license.

#include "bitboard_iterator.h"
#include "evaluation.h"
#include "file.h"
#include "rank.h"

static const int EVALUATION_MATERIAL[] =
{
    [PIECE_PAWN] = 100,
    [PIECE_KNIGHT] = 300,
    [PIECE_BISHOP] = 325,
    [PIECE_ROOK] = 500,
    [PIECE_QUEEN] = 900,
    [PIECE_KING] = 0
};

static const int EVALUATION_POSITION[][SQUARES] =
{
    [PIECE_PAWN] = 
    {
        90,  90,  90,  90,  90,  90,  90,  90,
        30,  30,  30,  40,  40,  30,  30,  30,
        20,  20,  20,  30,  30,  30,  20,  20,
        10,  10,  10,  20,  20,  10,  10,  10,
        5,   5,  10,  20,  20,   5,   5,   5,
        0,   0,   0,   5,   5,   0,   0,   0,
        0,   0,   0, -10, -10,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0
    },
    [PIECE_KNIGHT] =
    {
        -5,   0,   0,   0,   0,   0,   0,  -5,
        -5,   0,   0,  10,  10,   0,   0,  -5,
        -5,   5,  20,  20,  20,  20,   5,  -5,
        -5,  10,  20,  30,  30,  20,  10,  -5,
        -5,  10,  20,  30,  30,  20,  10,  -5,
        -5,   5,  20,  10,  10,  20,   5,  -5,
        -5,   0,   0,   0,   0,   0,   0,  -5,
        -5, -10,   0,   0,   0,   0, -10,  -5
    },
    [PIECE_BISHOP] =
    {
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        0,  20,   0,  10,  10,   0,  20,   0,
        0,   0,  10,  20,  20,  10,   0,   0,
        0,   0,  10,  20,  20,  10,   0,   0,
        0,  10,   0,   0,   0,   0,  10,   0,
        0,  30,   0,   0,   0,   0,  30,   0,
        0,   0, -10,   0,   0, -10,   0,   0
    },
    [PIECE_ROOK] =
    {
        50,  50,  50,  50,  50,  50,  50,  50,
        50,  50,  50,  50,  50,  50,  50,  50,
        0,   0,  10,  20,  20,  10,   0,   0,
        0,   0,  10,  20,  20,  10,   0,   0,
        0,   0,  10,  20,  20,  10,   0,   0,
        0,   0,  10,  20,  20,  10,   0,   0,
        0,   0,  10,  20,  20,  10,   0,   0,
        0,   0,   0,  20,  20,   0,   0,   0
    },
    [PIECE_KING] =
    {
        0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   5,   5,   5,   5,   0,   0,
        0,   5,   5,  10,  10,   5,   5,   0,
        0,   5,  10,  20,  20,  10,   5,   0,
        0,   5,  10,  20,  20,  10,   5,   0,
        0,   0,   5,  10,  10,   5,   0,   0,
        0,   5,   5,  -5,  -5,   0,   5,   0,
        0,   0,   5,   0, -15,   0,  10,   0
    }
};

int evaluation(Board board)
{
    int result = 0;

    for (Piece piece = PIECE_PAWN; piece <= PIECE_KING; piece++)
    {
        struct BitboardIterator it;
        uint64_t value = board->pieces[piece + PIECE_WHITE_PAWN];

        for (bitboard_begin(&it, value); it.value; bitboard_next(&it))
        {
            result += EVALUATION_MATERIAL[piece];
            result += EVALUATION_POSITION[piece][it.current];
        }

        value = board->pieces[piece + PIECE_BLACK_PAWN];
        
        for (bitboard_begin(&it, value); it.value; bitboard_next(&it))
        {
            Rank rank = RANKS - (it.current / FILES) - 1;
            File file = it.current % FILES;
            Square square = rank * FILES + file;

            result -= EVALUATION_MATERIAL[piece];
            result -= EVALUATION_POSITION[piece][square];
        }
    }

    if (board->color)
    {
        return -result;
    }

    return result;
}
