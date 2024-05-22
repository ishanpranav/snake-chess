// piece.c
// Licensed under the MIT license.

#include "piece.h"

static String PIECE_STRINGS[][PIECES + 1] =
{
    [ENCODING_ALGEBRAIC] =
    {
        "", "N", "B", "R", "Q", "K",
        "", "N", "B", "R", "Q", "K",
        "?"
    },
    [ENCODING_ASCII] =
    {
        "P", "N", "B", "R", "Q", "K",
        "p", "n", "b", "r", "q", "k",
        "."
    },
    [ENCODING_UNICODE] =
    {
        "\u2659", "\u2658", "\u2657", "\u2656", "\u2655", "\u2654",
        "\u265f", "\u265e", "\u265d", "\u265c", "\u265b", "\u265a",
        "."
    }
};

Piece piece_from_fen_char(char value)
{
    switch (value)
    {
    case 'P': return PIECE_WHITE_PAWN;
    case 'N': return PIECE_WHITE_KNIGHT;
    case 'B': return PIECE_WHITE_BISHOP;
    case 'R': return PIECE_WHITE_ROOK;
    case 'Q': return PIECE_WHITE_QUEEN;
    case 'K': return PIECE_WHITE_KING;
    case 'p': return PIECE_BLACK_PAWN;
    case 'n': return PIECE_BLACK_KNIGHT;
    case 'b': return PIECE_BLACK_BISHOP;
    case 'r': return PIECE_BLACK_ROOK;
    case 'q': return PIECE_BLACK_QUEEN;
    case 'k': return PIECE_BLACK_KING;
    default: return PIECES;
    }
}

String piece_to_string(Piece piece, Encoding encoding)
{
    return PIECE_STRINGS[encoding][piece];
}
