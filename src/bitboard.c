#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "bitboard.h"

void bitboard_reset(unsigned long long *this, enum Square square)
{
    if (!(*this & (1ull << square)))
    {
        return;
    }

    *this ^= (1ull << square);
}

void printBitboard(unsigned long long this)
{
    printf("\n       a b c d e f g h\n\n");

    for (int rank = 0; rank < 8; rank++)
    {
        printf("   %d  ", 8 - rank);

        for (int file = 0; file < 8; file++)
        {
            enum Square square = (rank * 8) + file;

            if (this & (1ull << square))
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

    printf("\nBitboard: %llx\n\n", this);
}
