// move.c
// Licensed under the MIT license.

#include "move.h"

void move_write_string(Stream output, Move instance)
{
    switch (instance->type)
    {
    case MOVE_TYPE_CASTLE_KINGSIDE:
        fprintf(output, "O-O");
        return;

    case MOVE_TYPE_CASTLE_QUEENSIDE:
        fprintf(output, "O-O-O");
        return;

    default: break;
    }

    fprintf(
        output,
        "%s%s",
        piece_to_string(instance->piece, ENCODING_ALGEBRAIC),
        square_to_string(instance->source));

    if (instance->type == MOVE_TYPE_CAPTURE ||
        instance->type == MOVE_TYPE_EN_PASSANT)
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

    if (instance->type == MOVE_TYPE_EN_PASSANT)
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
