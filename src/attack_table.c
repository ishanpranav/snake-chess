#include <stdlib.h>
#include "attack_table.h"
#include "bitboards.h"
#include "color.h"
#include "square.h"

struct AttackTable
{
    unsigned long long pawns[SQUARES][COLORS];
    unsigned long long knights[SQUARES];
    unsigned long long bishops[SQUARES];
    unsigned long long rooks[SQUARES];
    unsigned long long kings[SQUARES];
};

unsigned long long createPawnBitboard(enum Square square, enum Color color)
{
    unsigned long long result = 0ull;
    unsigned long long value = 1ull << square;
    unsigned long long h8Direction = value >> 7;
    unsigned long long a8Direction = value >> 9;
    unsigned long long a1Direction = value << 7;
    unsigned long long h1Direction = value << 9;

    switch (color)
    {
    case WHITE:
        if (h8Direction & FILE_NOT_A_MASK)
        {
            result |= h8Direction;
        }

        if (a8Direction & FILE_NOT_H_MASK)
        {
            result |= a8Direction;
        }

        break;

    case BLACK:
        if (a1Direction & FILE_NOT_H_MASK)
        {
            result |= a1Direction;
        }

        if (h1Direction & FILE_NOT_A_MASK)
        {
            result |= h1Direction;
        }
        break;
    }

    return result;
}

unsigned long long createKnightBitboard(enum Square square)
{
    unsigned long long result = 0ull;
    unsigned long long value = 1ull << square;
    unsigned long long piSixthsRadians = value >> 6;
    unsigned long long fivePiSixthsRadians = value >> 10;
    unsigned long long piThirdsRadians = value >> 15;
    unsigned long long twoPiThirdsRadians = value >> 17;
    unsigned long long sevenPiSixthsRadians = value << 6;
    unsigned long long elevenPiSixthsRadians = value << 10;
    unsigned long long fourPiThirdsRadians = value << 15;
    unsigned long long fivePiThirdsRadians = value << 17;

    if (piSixthsRadians & FILE_NOT_A_NOR_B_MASK)
    {
        result |= piSixthsRadians;
    }

    if (fivePiSixthsRadians & FILE_NOT_H_NOR_G_MASK)
    {
        result |= fivePiSixthsRadians;
    }

    if (piThirdsRadians & FILE_NOT_A_MASK)
    {
        result |= piThirdsRadians;
    }

    if (twoPiThirdsRadians & FILE_NOT_H_MASK)
    {
        result |= twoPiThirdsRadians;
    }

    if (sevenPiSixthsRadians & FILE_NOT_H_NOR_G_MASK)
    {
        result |= sevenPiSixthsRadians;
    }

    if (elevenPiSixthsRadians & FILE_NOT_A_NOR_B_MASK)
    {
        result |= elevenPiSixthsRadians;
    }

    if (fourPiThirdsRadians & FILE_NOT_H_MASK)
    {
        result |= fourPiThirdsRadians;
    }

    if (fivePiThirdsRadians & FILE_NOT_A_MASK)
    {
        result |= fivePiThirdsRadians;
    }

    return result;
}

unsigned long long createBishopBitboard(enum Square square)
{
    int destinationRank = square / 8;
    int destinationFile = square % 8;
    int rank = destinationRank + 1;
    int file = destinationFile + 1;
    unsigned long long result = 0ull;

    while (rank < 7 && file < 7)
    {
        result |= 1ull << (rank * 8 + file);
        rank++;
        file++;
    }

    rank = destinationRank - 1;
    file = destinationFile + 1;

    while (rank > 0 && file < 7)
    {
        result |= 1ull << (rank * 8 + file);
        rank--;
        file++;
    }

    rank = destinationRank + 1;
    file = destinationFile - 1;

    while (rank < 7 && file > 0)
    {
        result |= 1ull << (rank * 8 + file);
        rank++;
        file--;
    }

    rank = destinationRank - 1;
    file = destinationFile - 1;

    while (rank > 0 && file > 0)
    {
        result |= 1ull << (rank * 8 + file);
        rank--;
        file--;
    }

    return result;
}

unsigned long long getBishopAttacks(enum Square square, unsigned long long obstacles)
{
    int destinationRank = square / 8;
    int destinationFile = square % 8;
    int rank = destinationRank + 1;
    int file = destinationFile + 1;
    unsigned long long result = 0ull;

    while (rank <= 7 && file <= 7)
    {
        unsigned long long destination = 1ull << (rank * 8 + file);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }

        rank++;
        file++;
    }

    rank = destinationRank - 1;
    file = destinationFile + 1;

    while (rank >= 0 && file <= 7)
    {
        unsigned long long destination = 1ull << (rank * 8 + file);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }

        rank--;
        file++;
    }

    rank = destinationRank + 1;
    file = destinationFile - 1;

    while (rank <= 7 && file >= 0)
    {
        unsigned long long destination = 1ull << (rank * 8 + file);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }

        rank++;
        file--;
    }

    rank = destinationRank - 1;
    file = destinationFile - 1;

    while (rank >= 0 && file >= 0)
    {
        unsigned long long destination = 1ull << (rank * 8 + file);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }

        rank--;
        file--;
    }

    return result;
}

unsigned long long createRookBitboard(enum Square square)
{
    int destinationRank = square / 8;
    int destinationFile = square % 8;
    unsigned long long result = 0ull;

    for (int rank = destinationRank + 1; rank < 7; rank++)
    {
        result |= 1ull << (rank * 8 + destinationFile);
    }

    for (int rank = destinationRank - 1; rank > 0; rank--)
    {
        result |= 1ull << (rank * 8 + destinationFile);
    }

    for (int file = destinationFile + 1; file < 7; file++)
    {
        result |= 1ull << (destinationRank * 8 + file);
    }

    for (int file = destinationFile - 1; file > 0; file--)
    {
        result |= 1ull << (destinationRank * 8 + file);
    }

    return result;
}

unsigned long long getRookAttacks(enum Square square, unsigned long long obstacles)
{
    int destinationRank = square / 8;
    int destinationFile = square % 8;
    unsigned long long result = 0ull;

    for (int rank = destinationRank + 1; rank <= 7; rank++)
    {
        unsigned long long destination = 1ull << (rank * 8 + destinationFile);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }
    }

    for (int rank = destinationRank - 1; rank >= 0; rank--)
    {
        unsigned long long destination = 1ull << (rank * 8 + destinationFile);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }
    }

    for (int file = destinationFile + 1; file <= 7; file++)
    {
        unsigned long long destination = 1ull << (destinationRank * 8 + file);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }
    }

    for (int file = destinationFile - 1; file >= 0; file--)
    {
        unsigned long long destination = 1ull << (destinationRank * 8 + file);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }
    }

    return result;    
}

unsigned long long createKingBitboard(enum Square square)
{
    unsigned long long value = 1ull << square;
    unsigned long long fileA = value >> 1;
    unsigned long long h8 = value >> 7;
    unsigned long long rank8 = value >> 8;
    unsigned long long a8 = value >> 9;
    unsigned long long fileH = value << 1;
    unsigned long long a1 = value << 7;
    unsigned long long rank1 = value << 8;
    unsigned long long h1 = value << 9;
    unsigned long long result = rank1 | rank8;

    if (fileA & FILE_NOT_H_MASK)
    {
        result |= fileA;
    }

    if (h8 & FILE_NOT_A_MASK)
    {
        result |= h8;
    }

    if (a8 & FILE_NOT_H_MASK)
    {
        result |= a8;
    }

    if (fileH & FILE_NOT_A_MASK)
    {
        result |= fileH;
    }

    if (a1 & FILE_NOT_H_MASK)
    {
        result |= a1;
    }

    if (h1 & FILE_NOT_A_MASK)
    {
        result |= h1;
    }

    return result;
}

struct AttackTable *attack_table()
{
    struct AttackTable *instance = malloc(sizeof *instance);

    if (instance == NULL)
    {
        return NULL;
    }

    for (enum Square square = 0; square < SQUARES; square++)
    {
        for (enum Color color = 0; color < COLORS; color++)
        {
            instance->pawns[square][color] = createPawnBitboard(square, color);
        }

        instance->knights[square] = createKnightBitboard(square);
        instance->bishops[square] = createBishopBitboard(square);
        instance->rooks[square] = createRookBitboard(square);
        instance->kings[square] = createKingBitboard(square);
    }

    return instance;
}

void finalize_attack_table(struct AttackTable *this)
{
    free(this);
}
