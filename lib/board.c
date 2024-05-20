// board.c
// Licensed under the MIT license.

#include <string.h>
#include "bitboard.h"
#include "board.h"
#include "file.h"
#include "rank.h"

void board(Board instance)
{
    instance->castlingRights = CASTLING_RIGHTS_NONE;
    instance->color = COLOR_WHITE;
    instance->enPassant = SQUARES;
    instance->squares = 0;

    memset(instance->colors, 0, sizeof instance->colors);
    memset(instance->pieces, 0, sizeof instance->pieces);
}

static Piece board_get_occupant(Board instance, uint64_t square)
{
    for (Piece piece = 0; piece < PIECES; piece++)
    {
        if (instance->pieces[piece] & square)
        {
            return piece;
        }
    }

    return PIECES;
}

void board_write_string(Stream output, Board instance, Encoding encoding)
{
    fprintf(output, "\n");

    for (Rank rank = 0; rank < RANKS; rank++)
    {
        fprintf(output, "  %d  ", 8 - rank);

        for (File file = 0; file < FILES; file++)
        {
            uint64_t square = bitboard(rank * 8 + file);
            Piece piece = board_get_occupant(instance, square);

            fprintf(output, " %s ", piece_to_string(piece, encoding));
        }

        fprintf(output, "\n");
    }

    fprintf(
        output,
        "\n      a  b  c  d  e  f  g  h\n\n"
        "%s to move\n"
        "en passant: %s    castle: ",
        color_to_string(instance->color),
        square_to_string(instance->enPassant));
    castling_rights_write_string(output, instance->castlingRights);
    fprintf(output, "\n");
}
