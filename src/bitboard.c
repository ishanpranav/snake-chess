#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "bitboard.h"

bool bitboard_get(unsigned long long this, enum Square square)
{
    // GCC requires result stored in boolean
    bool result = this & (1ull << square);

    return result;
}

void bitboard_set(unsigned long long *this, enum Square square)
{
    *this |= (1ull << square);
}

void bitboard_reset(unsigned long long *this, enum Square square)
{
    if (!bitboard_get(*this, square))
    {
        return;
    }

    *this ^= (1ull << square);
}

void bitboard_print(unsigned long long this)
{
    printf("\n       a b c d e f g h\n\n");

    for (int rank = 0; rank < 8; rank++)
    {
        printf("   %d  ", 8 - rank);

        for (int file = 0; file < 8; file++)
        {
            enum Square square = (rank * 8) + file;

            if (bitboard_get(this, square))
            {
                printf(" 1");
            }
            else
            {
                printf(" 0");
            }
        }

        printf("\n");
    }

    printf("\nBitboard: %#018llx\n\n", this);
}
