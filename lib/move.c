// move.c
// Licensed under the MIT license.

#include "move.h"

void move_write_string(Stream output, Move value)
{
    if (value->castle)
    {
        fprintf(output, "O-O");

        if (value->source - value->target == 4)
        {
            fprintf(output, "-O");
        }

        return;
    }

    fprintf(
        output,
        "%s",
        piece_to_string(value->piece, ENCODING_ALGEBRAIC));

    if (value->capture)
    {
        fprintf(output, "x");
    }

    fprintf(output, "%s", value->target);

    if (value->promotion != PIECES)
    {
        fprintf(
            output,
            "=%s",
            piece_to_string(value->promotion, ENCODING_ALGEBRAIC));
    }

    if (value->enPassant)
    {
        fprintf(output, " e.p.");
    }
}

void move_write_uci_string(Stream output, Move value)
{
    fprintf(output, "%s%s%s",
        square_to_string(value->source),
        square_to_string(value->target),
        square_to_string(value->promotion));
}
