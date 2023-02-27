#include "attacks.h"
#include "bitboard.h"

unsigned long long mask_pawn_attacks(enum Color color, enum Square square)
{
    unsigned long long result = 0ull;
    unsigned long long bitboard = 0ull;

    bitboard_set(&bitboard, square);

    switch (color)
    {
    case WHITE:
        result |= (bitboard >> 7);
        break;

    case BLACK:
        break;
    }

    return result;
}
