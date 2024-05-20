// bitboard.c
// Licensed under the MIT license.

#include <inttypes.h>
#include "bitboard.h"
#include "file.h"
#include "rank.h"
#ifndef bitboard_count
int bitboard_count(uint64_t value)
{
    int result = 0;

    while (value)
    {
        result++;
        value &= value - 1;
    }

    return result;
}
#endif
#ifndef bitboard_first
Square bitboard_first(uint64_t value)
{
    if (!value)
    {
        return SQUARES;
    }

    return bitboard_count((value & -value) - 1);
}
#endif

void bitboard_write_string(FILE* output, uint64_t value)
{
    fprintf(output, "\n");

    for (Rank rank = 0; rank < RANKS; rank++)
    {
        fprintf(output, "  %d  ", 8 - rank);

        for (File file = 0; file < FILES; file++)
        {
            Square square = rank * 8 + file;

            fprintf(output, " %c ", value & bitboard(square) ? '#' : '.');
        }

        fprintf(output, "\n");
    }

    fprintf(
        output,
        "\n      a  b  c  d  e  f  g  h" "\n\n"
        "Dec: %" PRIu64 "\n"
        "Hex: 0x%" PRIx64 "\n",
        value,
        value);
}
