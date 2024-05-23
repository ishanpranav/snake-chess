// evaluation.c
// Licensed under the MIT license.

#include "bitboard_iterator.h"
#include "evaluation.h"

static const int EVALUATION_MATERIAL[] =
{
    [PIECE_PAWN] = 100,
    [PIECE_KNIGHT] = 300,
    [PIECE_BISHOP] = 325,
    [PIECE_ROOK] = 500,
    [PIECE_QUEEN] = 900,
    [PIECE_KING] = 0
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
        }

        value = board->pieces[piece + PIECE_BLACK_PAWN];
        
        for (bitboard_begin(&it, value); it.value; bitboard_next(&it))
        {
            result -= EVALUATION_MATERIAL[piece];
        }
    }

    if (board->color)
    {
        return -result;
    }

    return result;
}
