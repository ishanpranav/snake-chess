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

static uint64_t generate_bishop_mask(Square square)
{
    uint64_t result = 0;
    Rank targetRank = square / 8;
    File targetFile = square % 8;
    int rank = targetRank + 1;
    int file = targetFile + 1;

    while (rank <= RANK_SEVENTH && file <= FILE_G)
    {
        result |= bitboard(rank * 8 + file);
        rank++;
        file++;
    }

    rank = targetRank - 1;
    file = targetFile + 1;

    while (rank >= RANK_SECOND && file <= FILE_G)
    {
        result |= bitboard(rank * 8 + file);
        rank--;
        file++;
    }

    rank = targetRank + 1;
    file = targetFile - 1;

    while (rank <= RANK_SEVENTH && file >= FILE_B)
    {
        result |= bitboard(rank * 8 + file);
        rank++;
        file--;
    }

    rank = targetRank - 1;
    file = targetFile - 1;

    while (rank >= RANK_SECOND && file >= FILE_B)
    {
        result |= bitboard(rank * 8 + file);
        rank--;
        file--;
    }

    return result;
}

static uint64_t generate_rook_mask(Square square)
{
    uint64_t result = 0;
    Rank targetRank = square / 8;
    File targetFile = square % 8;

    for (Rank rank = targetRank + 1; rank <= RANK_SEVENTH; rank++)
    {
        result |= bitboard(rank * 8 + targetFile);
    }

    for (int rank = targetRank - 1; rank >= RANK_SECOND; rank--)
    {
        result |= bitboard(rank * 8 + targetFile);
    }

    for (File file = targetFile + 1; file <= FILE_G; file++)
    {
        result |= bitboard(targetRank * 8 + file);
    }

    for (int file = targetFile - 1; file >= FILE_B; file--)
    {
        result |= bitboard(targetRank * 8 + file);
    }

    return result;
}

static uint64_t generate_bishop_attacks(Square square, uint64_t obstacles)
{
    uint64_t result = 0;
    Rank targetRank = square / 8;
    File targetFile = square % 8;
    int rank = targetRank + 1;
    int file = targetFile + 1;

    while (rank < RANKS && file < FILES)
    {
        uint64_t target = bitboard(rank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }

        rank++;
        file++;
    }

    rank = targetRank - 1;
    file = targetFile + 1;

    while (rank >= 0 && file < FILES)
    {
        uint64_t target = bitboard(rank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }

        rank--;
        file++;
    }

    rank = targetRank + 1;
    file = targetFile - 1;

    while (rank < RANKS && file >= 0)
    {
        uint64_t target = bitboard(rank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }

        rank++;
        file--;
    }

    rank = targetRank - 1;
    file = targetFile - 1;

    while (rank >= 0 && file >= 0)
    {
        uint64_t target = bitboard(rank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }

        rank--;
        file--;
    }

    return result;
}

static uint64_t generate_rook_attacks(Square square, uint64_t obstacles)
{
    uint64_t result = 0;
    Rank targetRank = square / 8;
    File targetFile = square % 8;

    for (Rank rank = targetRank + 1; rank < RANKS; rank++)
    {
        uint64_t target = bitboard(rank * 8 + targetFile);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    for (int rank = targetRank - 1; rank >= 0; rank--)
    {
        uint64_t target = bitboard(rank * 8 + targetFile);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    for (File file = targetFile + 1; file < FILES; file++)
    {
        uint64_t target = bitboard(targetRank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    for (int file = targetFile - 1; file >= 0; file--)
    {
        uint64_t target = bitboard(targetRank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
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
    uint64_t obstacles = 0;

    bitboard_set(obstacles, SQUARE_D7);
    bitboard_set(obstacles, SQUARE_D2);
    bitboard_set(obstacles, SQUARE_D1);
    bitboard_set(obstacles, SQUARE_B4);
    bitboard_set(obstacles, SQUARE_G4);

    printf("%s\n", square_to_string(bitboard_first(obstacles)));

    // bitboard_write_string(stdout, obstacles);
    // bitboard_write_string(stdout, generate_rook_attacks(SQUARE_D4, obstacles));

    return 0;
}
