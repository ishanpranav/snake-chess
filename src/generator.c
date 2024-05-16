// generator.c
// Licensed under the MIT license.

#include "../lib/bitboard.h"
#include "../lib/color.h"
#include "../lib/file.h"
#include "../lib/rank.h"
#include "../lib/square.h"

uint64_t pawnAttacks[COLORS][SQUARES];

static uint64_t generate_white_pawn_attacks(Square square)
{
    uint64_t value = 0;

    bitboard_set(value, square);

    uint64_t result = 0;
    uint64_t a = value >> 7;
    uint64_t b = value >> 9;

    if (a & BITBOARD_NOT_FILE_A)
    {
        result |= a;
    }

    if (b & BITBOARD_NOT_FILE_H)
    {
        result |= b;
    }

    return result;
}

static uint64_t generate_black_pawn_attacks(Square square)
{
    uint64_t value = 0;

    bitboard_set(value, square);

    uint64_t result = 0;
    uint64_t a = value << 7;
    uint64_t b = value << 9;

    if (a & BITBOARD_NOT_FILE_H)
    {
        result |= a;
    }

    if (b & BITBOARD_NOT_FILE_A)
    {
        result |= b;
    }

    return result;
}

static void leaper_attack_table()
{
    for (Square square = 0; square < SQUARES; square++)
    {
        pawnAttacks[COLOR_WHITE][square] = generate_white_pawn_attacks(square);
        pawnAttacks[COLOR_BLACK][square] = generate_black_pawn_attacks(square);
    }
}

int main(void)
{
    return 0;
}
