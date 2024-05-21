// attack_table.c
// Licensed under the MIT license.

#include "attack_table.h"
#include "bitboard.h"
#include "rank.h"
#include "file.h"

static const uint64_t ATTACK_TABLE_BISHOP_MAGICS[] =
{
    #include "../data/bishop-magics.csv"
};

static const int ATTACK_TABLE_BISHOP_OCCUPANCY_LENGTHS[] =
{
    #include "../data/bishop-occupancy-lengths.csv"
};

static const uint64_t ATTACK_TABLE_ROOK_MAGICS[] =
{
    #include "../data/rook-magics.csv"
};

static const int ATTACK_TABLE_ROOK_OCCUPANCY_LENGTHS[] =
{
    #include "../data/rook-occupancy-lengths.csv"
};

static uint64_t attack_table_generate_white_pawns(Square square)
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

static uint64_t attack_table_generate_black_pawns(Square square)
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

static uint64_t attack_table_generate_knights(Square square)
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

static uint64_t attack_table_generate_kings(Square square)
{
    uint64_t result = 0;
    uint64_t value = bitboard(square);
    uint64_t a = value >> 1;
    uint64_t b = value >> 7;
    uint64_t c = value >> 8;
    uint64_t d = value >> 9;
    uint64_t e = value << 1;
    uint64_t f = value << 7;
    uint64_t g = value << 8;
    uint64_t h = value << 9;

    if (a & BITBOARD_NOT_FILE_H)
    {
        result |= a;
    }

    if (b & BITBOARD_NOT_FILE_A)
    {
        result |= b;
    }

    result |= c;

    if (d & BITBOARD_NOT_FILE_H)
    {
        result |= d;
    }

    if (e & BITBOARD_NOT_FILE_A)
    {
        result |= e;
    }

    if (f & BITBOARD_NOT_FILE_H)
    {
        result |= f;
    }

    result |= g;

    if (h & BITBOARD_NOT_FILE_A)
    {
        result |= h;
    }

    return result;
}

uint64_t attack_table_generate_bishop_relevant_occupancies(Square square)
{
    uint64_t result = 0;
    Rank targetRank = square / FILES;
    File targetFile = square % FILES;
    int rank = targetRank + 1;
    int file = targetFile + 1;

    while (rank <= RANK_SEVENTH && file <= FILE_G)
    {
        result |= bitboard(rank * FILES + file);
        rank++;
        file++;
    }

    rank = targetRank - 1;
    file = targetFile + 1;

    while (rank >= RANK_SECOND && file <= FILE_G)
    {
        result |= bitboard(rank * FILES + file);
        rank--;
        file++;
    }

    rank = targetRank + 1;
    file = targetFile - 1;

    while (rank <= RANK_SEVENTH && file >= FILE_B)
    {
        result |= bitboard(rank * FILES + file);
        rank++;
        file--;
    }

    rank = targetRank - 1;
    file = targetFile - 1;

    while (rank >= RANK_SECOND && file >= FILE_B)
    {
        result |= bitboard(rank * FILES + file);
        rank--;
        file--;
    }

    return result;
}

uint64_t attack_table_generate_rook_relevant_occupancies(Square square)
{
    uint64_t result = 0;
    Rank targetRank = square / FILES;
    File targetFile = square % FILES;

    for (Rank rank = targetRank + 1; rank <= RANK_SEVENTH; rank++)
    {
        result |= bitboard(rank * FILES + targetFile);
    }

    for (int rank = targetRank - 1; rank >= RANK_SECOND; rank--)
    {
        result |= bitboard(rank * FILES + targetFile);
    }

    for (File file = targetFile + 1; file <= FILE_G; file++)
    {
        result |= bitboard(targetRank * FILES + file);
    }

    for (int file = targetFile - 1; file >= FILE_B; file--)
    {
        result |= bitboard(targetRank * FILES + file);
    }

    return result;
}

uint64_t attack_table_generate_bishops(Square square, uint64_t obstacles)
{
    uint64_t result = 0;
    Rank targetRank = square / FILES;
    File targetFile = square % FILES;
    int rank = targetRank + 1;
    int file = targetFile + 1;

    while (rank < RANKS && file < FILES)
    {
        uint64_t target = bitboard(rank * FILES + file);

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
        uint64_t target = bitboard(rank * FILES + file);

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
        uint64_t target = bitboard(rank * FILES + file);

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
        uint64_t target = bitboard(rank * FILES + file);

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

uint64_t attack_table_generate_rooks(Square square, uint64_t obstacles)
{
    uint64_t result = 0;
    Rank targetRank = square / FILES;
    File targetFile = square % FILES;

    for (Rank rank = targetRank + 1; rank < RANKS; rank++)
    {
        uint64_t target = bitboard(rank * FILES + targetFile);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    for (int rank = targetRank - 1; rank >= 0; rank--)
    {
        uint64_t target = bitboard(rank * FILES + targetFile);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    for (File file = targetFile + 1; file < FILES; file++)
    {
        uint64_t target = bitboard(targetRank * FILES + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    for (int file = targetFile - 1; file >= 0; file--)
    {
        uint64_t target = bitboard(targetRank * FILES + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    return result;
}

static uint64_t attack_table_lookup_occupancies(
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

uint64_t attack_table_get_bishop(
    AttackTable instance,
    Square square,
    uint64_t obstacles)
{
    obstacles &= instance->bishopRelevantOccupancies[square];
    obstacles *= ATTACK_TABLE_BISHOP_MAGICS[square];
    obstacles >>= 64 - ATTACK_TABLE_BISHOP_OCCUPANCY_LENGTHS[square];

    return instance->bishops[square][obstacles];
}

uint64_t attack_table_get_rook(
    AttackTable instance,
    Square square,
    uint64_t obstacles)
{
    obstacles &= instance->rookRelevantOccupancies[square];
    obstacles *= ATTACK_TABLE_ROOK_MAGICS[square];
    obstacles >>= 64 - ATTACK_TABLE_ROOK_OCCUPANCY_LENGTHS[square];

    return instance->rooks[square][obstacles];
}

void attack_table(AttackTable instance)
{
    for (Square square = 0; square < SQUARES; square++)
    {
        instance->kings[square] = attack_table_generate_kings(square);
        instance->knights[square] = attack_table_generate_knights(square);
        instance->pawns[COLOR_WHITE][square] =
            attack_table_generate_white_pawns(square);
        instance->pawns[COLOR_BLACK][square] =
            attack_table_generate_black_pawns(square);

        uint64_t relevantOccupancies =
            attack_table_generate_bishop_relevant_occupancies(square);
        uint64_t magic = ATTACK_TABLE_BISHOP_MAGICS[square];
        int length = bitboard_count(relevantOccupancies);
        int count = 1 << length;
        int occupanciesLength = ATTACK_TABLE_BISHOP_OCCUPANCY_LENGTHS[square];

        instance->bishopRelevantOccupancies[square] = relevantOccupancies;

        for (int index = 0; index < count; index++)
        {
            uint64_t occupancies = attack_table_lookup_occupancies(
                index,
                length,
                relevantOccupancies);
            int key = (occupancies * magic) >> (64 - occupanciesLength);

            instance->bishops[square][key] =
                attack_table_generate_bishops(square, occupancies);
        }

        relevantOccupancies =
            attack_table_generate_rook_relevant_occupancies(square);
        magic = ATTACK_TABLE_ROOK_MAGICS[square];
        length = bitboard_count(relevantOccupancies);
        count = 1 << length;
        occupanciesLength = ATTACK_TABLE_ROOK_OCCUPANCY_LENGTHS[square];
        instance->rookRelevantOccupancies[square] = relevantOccupancies;

        for (int index = 0; index < count; index++)
        {
            uint64_t occupancies = attack_table_lookup_occupancies(
                index,
                length,
                relevantOccupancies);
            int key = (occupancies * magic) >> (64 - occupanciesLength);

            instance->rooks[square][key] =
                attack_table_generate_rooks(square, occupancies);
        }
    }
}
