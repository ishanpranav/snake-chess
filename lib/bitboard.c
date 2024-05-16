// bitboard.c
// Licensed under the MIT license.

#include <inttypes.h>
#include "bitboard.h"
#include "file.h"
#include "rank.h"
#include "square.h"

void bitboard_write_string(FILE* output, uint64_t value)
{
    fprintf(output, "\n");

    for (Rank rank = 0; rank < RANKS; rank++)
    {
        fprintf(output, "  %d  ", 8 - rank);

        for (File file = 0; file < FILES; file++)
        {
            Square square = rank * 8 + file;

            fprintf(output, " %d ", bitboard_get(value, square) ? 1 : 0);
        }

        fprintf(output, "\n");
    }

    fprintf(
        output,
        "\n      a  b  c  d  e  f  g  h\n\nValue: %" PRIu64 "\n",
        value);
}
