// board.h
// Licensed under the MIT license.

#include <stdint.h>
#include "../ishan/stream.h"
#include "castling_rights.h"
#include "piece.h"
#include "square.h"
#define BOARD_EMPTY "8/8/8/8/8/8/8/8 w - -"
#define BOARD_INITIAL "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1"

/** */
struct Board
{
    uint64_t squares;
    uint64_t colors[COLORS];
    uint64_t pieces[PIECES];
    CastlingRights castlingRights;
    Color color;
    Square enPassant;
};

/** */
typedef struct Board* Board;

/**
 *
 * @param instance
*/
void board(Board instance);

/**
 *
 * @param result
 * @param value
*/
void board_from_fen_string(Board result, String value);

/**
 *
 * @param output
 * @param instance
 * @param encoding
*/
void board_write_string(Stream output, Board instance, Encoding encoding);
