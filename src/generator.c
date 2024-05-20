// generator.c
// Licensed under the MIT license.

#include "../lib/bitboard.h"
#include "../lib/color.h"
#include "../lib/file.h"
#include "../lib/rank.h"

uint64_t pawnAttacks[COLORS][SQUARES];
uint64_t knightAttacks[SQUARES];
uint64_t kingAttacks[SQUARES];

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

static uint64_t generate_knight_attacks(Square square)
{
    uint64_t value = 0;
    uint64_t result = 0;

    bitboard_set(value, square);

    uint64_t a = value >> 6;
    uint64_t b = value >> 10;
    uint64_t c = value >> 15;
    uint64_t d = value >> 17;
    uint64_t e = value << 6;
    uint64_t f = value << 10;
    uint64_t g = value << 15;
    uint64_t h = value << 17;

    if (a & BITBOARD_NOT_FILES_A_OR_B)
    {
        result |= a;
    }

    if (b & BITBOARD_NOT_FILES_H_OR_G)
    {
        result |= b;
    }

    if (c & BITBOARD_NOT_FILE_A)
    {
        result |= c;
    }

    if (d & BITBOARD_NOT_FILE_H)
    {
        result |= d;
    }

    if (e & BITBOARD_NOT_FILES_H_OR_G)
    {
        result |= e;
    }

    if (f & BITBOARD_NOT_FILES_A_OR_B)
    {
        result |= f;
    }

    if (g & BITBOARD_NOT_FILE_H)
    {
        result |= g;
    }

    if (h & BITBOARD_NOT_FILE_A)
    {
        result |= h;
    }

    return result;
}

static uint64_t generate_king_attacks(Square square)
{
    uint64_t value = 0;
    uint64_t result = 0;

    bitboard_set(value, square);

    uint64_t a = value >> 1;

    if (a & BITBOARD_NOT_FILE_H)
    {
        result |= a;
    }

    uint64_t b = value >> 7;

    if (b & BITBOARD_NOT_FILE_A)
    {
        result |= b;
    }

    result |= (value >> 8);

    uint64_t d = value >> 9;

    if (d & BITBOARD_NOT_FILE_H)
    {
        result |= d;
    }

    uint64_t e = value << 1;

    if (e & BITBOARD_NOT_FILE_A)
    {
        result |= e;
    }

    uint64_t f = value << 7;

    if (f & BITBOARD_NOT_FILE_H)
    {
        result |= f;
    }

    result |= (value << 8);

    uint64_t h = value << 9;

    if (h & BITBOARD_NOT_FILE_A)
    {
        result |= h;
    }

    return result;
}

static void leaper_attack_table()
{
    for (Square square = 0; square < SQUARES; square++)
    {
        pawnAttacks[COLOR_WHITE][square] = generate_white_pawn_attacks(square);
        pawnAttacks[COLOR_BLACK][square] = generate_black_pawn_attacks(square);
        knightAttacks[square] = generate_knight_attacks(square);
        kingAttacks[square] = generate_king_attacks(square);
    }
}

int main(void)
{
    leaper_attack_table();

    return 0;
}
