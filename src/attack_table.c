#include <stdlib.h>
#include "attack_table.h"
#include "bitboards.h"
#include "color.h"
#include "compiler.h"
#include "square.h"
#include "uint64.h"

struct AttackTable
{
    UInt64 pawns[SQUARES][COLORS];
    UInt64 knights[SQUARES];
    UInt64 bishops[SQUARES];
    UInt64 rooks[SQUARES];
    UInt64 kings[SQUARES];
};

static UInt64 createPawnBitboard(Square square, Color color)
{
    UInt64 result = 0ull;
    UInt64 value = 1ull << square;
    UInt64 h8Direction = value >> 7;
    UInt64 a8Direction = value >> 9;
    UInt64 a1Direction = value << 7;
    UInt64 h1Direction = value << 9;

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

static UInt64 createKnightBitboard(Square square)
{
    UInt64 result = 0ull;
    UInt64 value = 1ull << square;
    UInt64 piSixthsRadians = value >> 6;
    UInt64 fivePiSixthsRadians = value >> 10;
    UInt64 piThirdsRadians = value >> 15;
    UInt64 twoPiThirdsRadians = value >> 17;
    UInt64 sevenPiSixthsRadians = value << 6;
    UInt64 elevenPiSixthsRadians = value << 10;
    UInt64 fourPiThirdsRadians = value << 15;
    UInt64 fivePiThirdsRadians = value << 17;

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

static UInt64 createBishopBitboard(Square square)
{
    int destinationRank = square / 8;
    int destinationFile = square % 8;
    int rank = destinationRank + 1;
    int file = destinationFile + 1;
    UInt64 result = 0ull;

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

static UInt64 getBishopAttacks(Square square, UInt64 obstacles)
{
    int destinationRank = square / 8;
    int destinationFile = square % 8;
    int rank = destinationRank + 1;
    int file = destinationFile + 1;
    UInt64 result = 0ull;

    while (rank <= 7 && file <= 7)
    {
        UInt64 destination = 1ull << (rank * 8 + file);

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
        UInt64 destination = 1ull << (rank * 8 + file);

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
        UInt64 destination = 1ull << (rank * 8 + file);

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
        UInt64 destination = 1ull << (rank * 8 + file);

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

static UInt64 createRookBitboard(Square square)
{
    int destinationRank = square / 8;
    int destinationFile = square % 8;
    UInt64 result = 0ull;

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

static UInt64 getRookAttacks(Square square, UInt64 obstacles)
{
    int destinationRank = square / 8;
    int destinationFile = square % 8;
    UInt64 result = 0ull;

    for (int rank = destinationRank + 1; rank <= 7; rank++)
    {
        UInt64 destination = 1ull << (rank * 8 + destinationFile);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }
    }

    for (int rank = destinationRank - 1; rank >= 0; rank--)
    {
        UInt64 destination = 1ull << (rank * 8 + destinationFile);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }
    }

    for (int file = destinationFile + 1; file <= 7; file++)
    {
        UInt64 destination = 1ull << (destinationRank * 8 + file);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }
    }

    for (int file = destinationFile - 1; file >= 0; file--)
    {
        UInt64 destination = 1ull << (destinationRank * 8 + file);

        result |= destination;

        if (destination & obstacles)
        {
            break;
        }
    }

    return result;
}

static UInt64 createKingBitboard(Square square)
{
    UInt64 value = 1ull << square;
    UInt64 fileA = value >> 1;
    UInt64 h8 = value >> 7;
    UInt64 rank8 = value >> 8;
    UInt64 a8 = value >> 9;
    UInt64 fileH = value << 1;
    UInt64 a1 = value << 7;
    UInt64 rank1 = value << 8;
    UInt64 h1 = value << 9;
    UInt64 result = rank1 | rank8;

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

static UInt64 setOccupancy(int index, int count, UInt64 mask)
{
    UInt64 result = 0ull;

    for (int i = 0; i < count; i++)
    {
        enum Square square = ctzull(mask);
        UInt64 destination = 1ull << square;

        if (mask & destination)
        {
            mask ^= destination;
        }

        if (index & (1ull << i))
        {
            result |= 1ull << square;
        }
    }

    return result;
}

AttackTable attack_table()
{
    AttackTable instance = malloc(sizeof *instance);

    if (instance == NULL)
    {
        return NULL;
    }

    for (Square square = 0; square < SQUARES; square++)
    {
        for (Color color = 0; color < COLORS; color++)
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

void finalize_attack_table(AttackTable this)
{
    free(this);
}
