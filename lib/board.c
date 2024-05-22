// board.c
// Licensed under the MIT license.

#include <ctype.h>
#include <string.h>
#include "bitboard.h"
#include "board.h"
#include "file.h"
#include "rank.h"

static void board_clean(Board instance)
{
    instance->squares = 0;

    memset(instance->colors, 0, sizeof instance->colors);
}

void board(Board instance)
{
    instance->castlingRights = CASTLING_RIGHTS_NONE;
    instance->color = COLOR_WHITE;
    instance->enPassant = SQUARES;

    board_clean(instance);
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

void board_save_changes(Board instance)
{
    board_clean(instance);

    for (Piece piece = PIECE_WHITE_PAWN; piece <= PIECE_WHITE_KING; piece++)
    {
        instance->colors[COLOR_WHITE] |= instance->pieces[piece];
    }

    for (Piece piece = PIECE_BLACK_PAWN; piece <= PIECE_BLACK_KING; piece++)
    {
        instance->colors[COLOR_BLACK] |= instance->pieces[piece];
    }

    for (Color color = 0; color < COLORS; color++)
    {
        instance->squares |= instance->colors[color];
    }
}

void board_from_fen_string(Board result, String value)
{
    memset(result->pieces, 0, sizeof result->pieces);

    for (Rank rank = 0; rank < RANKS; rank++)
    {
        for (File file = 0; file < FILES; value++)
        {
            Piece piece = piece_from_fen_char(*value);

            if (piece != PIECES)
            {
                result->pieces[piece] |= bitboard(rank * FILES + file);
                file++;

                continue;
            }

            if (isdigit(*value))
            {
                int offset = *value - '0';

                file += offset;
            }
        }
    }

    value++;
    result->color = color_from_fen_char(*value);
    value += 2;
    result->castlingRights = castling_rights_from_fen_string(value);

    for (; *value && *value != ' '; value++) {}

    value++;
    result->enPassant = square_from_fen_string(value);

    board_save_changes(result);
}

void board_write_string(Stream output, Board instance, Encoding encoding)
{
    fprintf(output, "\n");

    for (Rank rank = 0; rank < RANKS; rank++)
    {
        fprintf(output, "  %d  ", RANKS - rank);

        for (File file = 0; file < FILES; file++)
        {
            uint64_t square = bitboard(rank * FILES + file);
            Piece piece = board_get_occupant(instance, square);

            fprintf(output, " %s ", piece_to_string(piece, encoding));
        }

        fprintf(output, "\n");
    }

    fprintf(
        output,
        "\n      a  b  c  d  e  f  g  h\n\n"
        "%s to move\n"
        "en passant: %s  castle: ",
        color_to_string(instance->color),
        square_to_string(instance->enPassant));
    castling_rights_write_string(output, instance->castlingRights);
    fprintf(output, "\n");
}
