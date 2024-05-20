// piece.h
// Licensed under the MIT license.

#include "../ishan/euler.h"
#include "color.h"
#include "encoding.h"

/** */
enum Piece
{
    PIECE_WHITE_PAWN,
    PIECE_WHITE_KNIGHT,
    PIECE_WHITE_BISHOP,
    PIECE_WHITE_ROOK,
    PIECE_WHITE_QUEEN,
    PIECE_WHITE_KING,
    PIECE_BLACK_PAWN,
    PIECE_BLACK_KNIGHT,
    PIECE_BLACK_BISHOP,
    PIECE_BLACK_ROOK,
    PIECE_BLACK_QUEEN,
    PIECE_BLACK_KING,
    PIECES
};

/** */
typedef enum Piece Piece;

/**
 *
 * @param value
 * @return
*/
Piece piece_from_ascii_char(char value);

/**
 *
 * @param value
 * @return
*/
String piece_to_string(Piece piece, Encoding encoding);
