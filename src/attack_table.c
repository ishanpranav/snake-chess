#include <stdio.h>
#include <stdlib.h>
#include "attack_table.h"
#include "bitboard.h"
#define NOT_FILE_A_MASK 0xfefefefefefefefeul
#define NOT_FILE_H_MASK 0x7f7f7f7f7f7f7f7ful

unsigned long long createPawnBitboard(enum Color color, enum Square square)
{
    unsigned long long result = 0ull;
    unsigned long long bitboard = 0ull;

    bitboard_set(&bitboard, square);

    switch (color)
    {
    case WHITE:
        if ((bitboard >> 7) & NOT_FILE_A_MASK)
        {
            result |= (bitboard >> 7);
        }

        if ((bitboard >> 9) & NOT_FILE_H_MASK)
        {
            result |= (bitboard >> 9);
        }

        break;

    case BLACK:
        if ((bitboard << 7) & NOT_FILE_H_MASK)
        {
            result |= (bitboard << 7);
        }

        if ((bitboard << 9) & NOT_FILE_A_MASK)
        {
            result |= (bitboard << 9);
        }
        break;
    }

    return result;
}

struct AttackTable
{
    unsigned long long pawns[2][64];
};

struct AttackTable *attack_table()
{
    struct AttackTable *instance = malloc(sizeof *instance);

    for (enum Color color = WHITE; color <= BLACK; color++)
    {
        for (enum Square square = A8; square <= H1; square++)
        {
            instance->pawns[color][square] = createPawnBitboard(color, square);
        }
    }

    return instance;
}

void finalize_attack_table(struct AttackTable *this)
{
    free(this);
}
