// generator.c
// Licensed under the MIT license.

#include "../lib/bitboard.h"
#include "../lib/color.h"
#include "../lib/file.h"
#include "../lib/rank.h"

static const uint64_t BISHOP_MAGICS[] =
{
    #include "../data/bishop-magics.csv"
};

static const int BISHOP_OCCUPANCY_LENGTHS[] =
{
    #include "../data/bishop-occupancy-lengths.csv"
};

static const uint64_t ROOK_MAGICS[] =
{
    #include "../data/rook-magics.csv"
};

static const int ROOK_OCCUPANCY_LENGTHS[] =
{
    #include "../data/rook-occupancy-lengths.csv"
};

uint64_t pawnAttacks[COLORS][SQUARES];
uint64_t knightAttacks[SQUARES];
uint64_t kingAttacks[SQUARES];
uint64_t bishopRelevantOccupancies[SQUARES];
uint64_t rookRelevantOccupancies[SQUARES];
uint64_t bishopAttacks[SQUARES][512];
uint64_t rookAttacks[SQUARES][4096];

static uint64_t generate_white_pawn_attacks(Square square)
{
    uint64_t value = bitboard(square);
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
    uint64_t value = bitboard(square);
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
    uint64_t value = bitboard(square);
    uint64_t result = 0;
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
    uint64_t result = bitboard(square);
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

uint64_t generate_bishop_relevant_occupancies(Square square)
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

uint64_t generate_rook_relevant_occupancies(Square square)
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

uint64_t generate_bishop_attacks(Square square, uint64_t obstacles)
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

uint64_t generate_rook_attacks(Square square, uint64_t obstacles)
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

static uint64_t lookup_occupancies(
    int index,
    int length,
    uint64_t relevantOccupancies)
{
    uint64_t result = 0;

    for (int sublength = 0; sublength < length; sublength++)
    {
        Square square = bitboard_first(relevantOccupancies);

        relevantOccupancies &= ~bitboard(square);

        if (index & (1 << sublength))
        {
            result |= bitboard(square);
        }
    }

    return result;
}

static void attack_table()
{
    for (Square square = 0; square < SQUARES; square++)
    {
        pawnAttacks[COLOR_WHITE][square] = generate_white_pawn_attacks(square);
        pawnAttacks[COLOR_BLACK][square] = generate_black_pawn_attacks(square);
        knightAttacks[square] = generate_knight_attacks(square);
        kingAttacks[square] = generate_king_attacks(square);

        uint64_t relevantOccupancies =
            generate_bishop_relevant_occupancies(square);
        uint64_t magic = BISHOP_MAGICS[square];
        int length = bitboard_count(relevantOccupancies);
        int count = 1 << length;
        int occupanciesLength = BISHOP_OCCUPANCY_LENGTHS[square];

        bishopRelevantOccupancies[square] = relevantOccupancies;

        for (int index = 0; index < count; index++)
        {
            uint64_t occupancies = lookup_occupancies(
                index,
                length,
                relevantOccupancies);
            int key = (occupancies * magic) >> (64 - occupanciesLength);

            bishopAttacks[square][key] =
                generate_bishop_attacks(square, occupancies);
        }

        relevantOccupancies = generate_rook_relevant_occupancies(square);
        magic = ROOK_MAGICS[square];
        length = bitboard_count(relevantOccupancies);
        count = 1 << length;
        occupanciesLength = ROOK_OCCUPANCY_LENGTHS[square];
        rookRelevantOccupancies[square] = relevantOccupancies;

        for (int index = 0; index < count; index++)
        {
            uint64_t occupancies = lookup_occupancies(
                index,
                length,
                relevantOccupancies);
            int key = (occupancies * magic) >> (64 - occupanciesLength);

            rookAttacks[square][key] =
                generate_rook_attacks(square, occupancies);
        }
    }
}

static uint64_t get_bishop_attacks(Square square, uint64_t obstacles)
{
    obstacles &= bishopRelevantOccupancies[square];
    obstacles *= BISHOP_MAGICS[square];
    obstacles >>= 64 - BISHOP_OCCUPANCY_LENGTHS[square];

    return bishopAttacks[square][obstacles];
}

static uint64_t get_rook_attacks(Square square, uint64_t obstacles)
{
    obstacles &= rookRelevantOccupancies[square];
    obstacles *= ROOK_MAGICS[square];
    obstacles >>= 64 - ROOK_OCCUPANCY_LENGTHS[square];

    return rookAttacks[square][obstacles];
}

int main(void)
{
    attack_table();

    uint64_t obstacles = 0;

    obstacles |= bitboard(SQUARE_C5);
    obstacles |= bitboard(SQUARE_F2);
    obstacles |= bitboard(SQUARE_G7);
    obstacles |= bitboard(SQUARE_B2);
    obstacles |= bitboard(SQUARE_G5);
    obstacles |= bitboard(SQUARE_E2);
    obstacles |= bitboard(SQUARE_E7);

    bitboard_write_string(stdout, get_bishop_attacks(SQUARE_D4, obstacles));
    bitboard_write_string(stdout, get_rook_attacks(SQUARE_E5, obstacles));

    return 0;
}
