// move.c
// Licensed under the MIT license.

#include "move.h"

void move_write_string(Stream output, Move instance)
{
    if (instance->castle)
    {
        fprintf(output, "O-O");

        if (instance->source - instance->target == 4)
        {
            fprintf(output, "-O");
        }

        return;
    }

    fprintf(
        output,
        "%s%s",
        piece_to_string(instance->piece, ENCODING_ALGEBRAIC),
        square_to_string(instance->source));

    if (instance->capture)
    {
        fprintf(output, "x");
    }

    fprintf(output, "%s", square_to_string(instance->target));

    if (instance->promotion != PIECES)
    {
        fprintf(
            output,
            "=%s",
            piece_to_string(instance->promotion, ENCODING_ALGEBRAIC));
    }

    if (instance->enPassant)
    {
        fprintf(output, " e.p.");
    }
}

void move_write_uci_string(Stream output, Move instance)
{
    fprintf(output, "%s%s%s",
        square_to_string(instance->source),
        square_to_string(instance->target),
        piece_to_string(instance->promotion, ENCODING_UCI));
}
