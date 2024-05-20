// piece.c
// Licensed under the MIT license.

#include "piece.h"

static String PIECE_STRINGS[][PIECES + 1] =
{
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

static const Piece CHAR_PIECE_MAPPING[] =
{
    ['P'] = PIECE_WHITE_PAWN,
    ['N'] = PIECE_WHITE_KNIGHT,
    ['B'] = PIECE_WHITE_BISHOP,
    ['R'] = PIECE_WHITE_ROOK,
    ['Q'] = PIECE_WHITE_QUEEN,
    ['K'] = PIECE_WHITE_KING,
    ['p'] = PIECE_BLACK_PAWN,
    ['n'] = PIECE_BLACK_KNIGHT,
    ['b'] = PIECE_BLACK_BISHOP,
    ['q'] = PIECE_BLACK_QUEEN,
    ['k'] = PIECE_BLACK_KING
};

Piece piece_from_ascii_char(char value)
{
    return CHAR_PIECE_MAPPING[(int)value];
}

String piece_to_string(Piece piece, Encoding encoding)
{
    return PIECE_STRINGS[encoding][piece];
}
