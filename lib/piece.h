// piece.h
// Licensed under the MIT license.

#ifndef PIECE_db8a1b354e774782808dc92d4060d7be
#define PIECE_db8a1b354e774782808dc92d4060d7be
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
    PIECES,
    PIECE_PAWN = PIECE_WHITE_PAWN,
    PIECE_KNIGHT = PIECE_WHITE_KNIGHT,
    PIECE_BISHOP = PIECE_WHITE_BISHOP,
    PIECE_ROOK = PIECE_WHITE_ROOK,
    PIECE_QUEEN = PIECE_WHITE_QUEEN,
    PIECE_KING = PIECE_WHITE_KING
};

/** */
typedef enum Piece Piece;

/**
 *
 * @param value
 * @return
*/
Piece piece_from_fen_char(char value);

/**
 *
 * @param value
 * @return
*/
String piece_to_string(Piece piece, Encoding encoding);

#endif
