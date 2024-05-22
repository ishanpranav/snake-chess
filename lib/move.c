// move.c
// Licensed under the MIT license.

#include "move.h"

void move_write_string(Stream output, Move instance)
{
    if (instance->type & MOVE_TYPES_CASTLE_KINGSIDE)
    {
        fprintf(output, "O-O");

        return;
    }

    if (instance->type & MOVE_TYPES_CASTLE_QUEENSIDE)
    {
        fprintf(output, "O-O-O");

        return;
    }

    fprintf(
        output,
        "%s%s",
        piece_to_string(instance->piece, ENCODING_ALGEBRAIC),
        square_to_string(instance->source));

    if (instance->type & MOVE_TYPES_CAPTURE)
    {
        fprintf(output, "x");
    }

    fprintf(output, "%s", square_to_string(instance->target));

    if (instance->type & MOVE_TYPES_PROMOTION_KNIGHT)
    {
        fprintf(output, "=N");

        return;
    }

    if (instance->type & MOVE_TYPES_PROMOTION_BISHOP)
    {
        fprintf(output, "=B");

        return;
    }

    if (instance->type & MOVE_TYPES_PROMOTION_ROOK)
    {
        fprintf(output, "=R");

        return;
    }

    if (instance->type & MOVE_TYPES_PROMOTION_QUEEN)
    {
        fprintf(output, "=Q");
    }
    
    if (instance->type & MOVE_TYPES_EN_PASSANT)
    {
        fprintf(output, " e.p.");
    }
}

void move_write_uci_string(Stream output, Move instance)
{
    fprintf(
        output,
        "%s%s",
        square_to_string(instance->source),
        square_to_string(instance->target));

    if (instance->type & MOVE_TYPES_PROMOTION_KNIGHT)
    {
        fprintf(output, "n");

        return;
    }
    
    if (instance->type & MOVE_TYPES_PROMOTION_BISHOP)
    {
        fprintf(output, "b");

        return;
    }

    if (instance->type & MOVE_TYPES_PROMOTION_ROOK)
    {
        fprintf(output, "r");

        return;
    }

    if (instance->type & MOVE_TYPES_PROMOTION_QUEEN)
    {
        fprintf(output, "q");

        return;
    }
}
