#include <stdio.h>
#include <stdlib.h>
#include "attack_table.h"
#include "bitboard.h"
#define FILE_NOT_A_MASK 0xfefefefefefefefeul
#define FILE_NOT_A_NOR_B_MASK 0xfcfcfcfcfcfcfcfc
#define FILE_NOT_H_MASK 0x7f7f7f7f7f7f7f7ful
#define FILE_NOT_H_NOR_G_MASK 0x3f3f3f3f3f3f3f3f

struct AttackTable
{
    unsigned long long pawns[SQUARES][2];
    unsigned long long knights[SQUARES];
};

unsigned long long createPawnBitboard(enum Square square, enum Color color)
{
    unsigned long long result = 0ull;
    unsigned long long value = bitboard(square);

    switch (color)
    {
    case WHITE:
        if ((value >> 7) & FILE_NOT_A_MASK)
        {
            result |= (value >> 7);
        }

        if ((value >> 9) & FILE_NOT_H_MASK)
        {
            result |= (value >> 9);
        }

        break;

    case BLACK:
        if ((value << 7) & FILE_NOT_H_MASK)
        {
            result |= (value << 7);
        }

        if ((value << 9) & FILE_NOT_A_MASK)
        {
            result |= (value << 9);
        }
        break;
    }

    return result;
}

unsigned long long createKnightBitboard(enum Square square)
{
    unsigned long long result = 0ull;
    unsigned long long value = bitboard(square);

    if ((value >> 17) & FILE_NOT_H_MASK)
    {
        result |= (value >> 17);
    }

    if ((value >> 15) & FILE_NOT_A_MASK)
    {
        result |= (value >> 15);
    }

    if ((value >> 10) & FILE_NOT_H_NOR_G_MASK)
    {
        result |= (value >> 10);
    }

    if ((value >> 6) & FILE_NOT_A_NOR_B_MASK)
    {
        result |= (value >> 6);
    }

    if ((value << 17) & FILE_NOT_A_MASK)
    {
        result |= (value << 17);
    }

    if ((value << 15) & FILE_NOT_H_MASK)
    {
        result |= (value << 15);
    }

    if ((value << 10) & FILE_NOT_A_NOR_B_MASK)
    {
        result |= (value << 10);
    }

    if ((value << 6) & FILE_NOT_H_NOR_G_MASK)
    {
        result |= (value << 6);
    }

    return result;
}

struct AttackTable *attack_table()
{
    struct AttackTable *instance = malloc(sizeof *instance);

    for (enum Square square = 0; square < SQUARES; square++)
    {
        for (enum Color color = 0; color <= COLORS; color++)
        {
            instance->pawns[square][color] = createPawnBitboard(square, color);
        }

        instance->knights[square] = createKnightBitboard(square);
    }

    return instance;
}

void finalize_attack_table(struct AttackTable *this)
{
    free(this);
}
