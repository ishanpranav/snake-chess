// board.h
// Licensed under the MIT license.

#ifndef BOARD_f50ed6f74b684b76ba9d00fa2bbdb84b
#define BOARD_f50ed6f74b684b76ba9d00fa2bbdb84b
#include <stdint.h>
#include "../ishan/stream.h"
#include "castling_rights.h"
#include "piece.h"
#include "square.h"
#include "zobrist.h"
#define BOARD_EMPTY "8/8/8/8/8/8/8/8 w - -"
#define BOARD_INITIAL "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define BOARD_INCREMENTAL_HASH 0
#if BOARD_INCREMENTAL_HASH
#define board_increment_hash(board, increment) (board)->hash ^= (increment)
#else
#define board_increment_hash(board, increment) 
#endif

/** */
struct Board
{
    uint64_t squares;
    uint64_t colors[COLORS];
    uint64_t pieces[PIECES];
    uint64_t hash;
    enum Color color;
    enum Square enPassant;
    enum CastlingRights castlingRights;
};

/** */
typedef struct Board* Board;

/**
 *
 * @param instance
 * @param zobrist
*/
void board(Board instance, Zobrist zobrist);

/**
 *
 * @param result
 * @param value
 * @param zobrist
*/
void board_from_fen_string(Board result, String value, Zobrist zobrist);

/**
 *
 * @param instance
*/
void board_save_changes(Board instance);

/**
 *
 * @param output
 * @param instance
 * @param encoding
*/
void board_write_string(Stream output, Board instance, Encoding encoding);

/**
 *
 * @param instance
 * @param zobrist
 * @return
*/
uint64_t board_hash(Board instance, Zobrist zobrist);

#endif
