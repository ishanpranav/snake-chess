// zobrist.c
// Licensed under the MIT license.

#include "../ishan/random.h"
#include "bitboard_iterator.h"
#include "zobrist.h"

void zobrist(Zobrist instance, uint32_t* state)
{
    for (Piece piece = 0; piece < PIECES; piece++)
    {
        for (Square square = 0; square < SQUARES; square++)
        {
            instance->pieces[piece][square] = xorshift32_random64(state);
        }
    }

    instance->color = xorshift32_random64(state);

    for (Square square = 0; square < SQUARES; square++)
    {
        instance->enPassant[square] = xorshift32_random64(state);
    }

    for (CastlingRights right = 0; right < CASTLING_RIGHTS; right++)
    {
        instance->castlingRights[right] = xorshift32_random64(state);
    }
}
