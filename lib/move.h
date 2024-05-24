// move.h
// Licensed under the MIT license.

#ifndef MOVE_351d83c941e240319a15515b2aa24a1d
#define MOVE_351d83c941e240319a15515b2aa24a1d
#include <stdbool.h>
#include "../ishan/stream.h"
#include "attack_table.h"
#include "board.h"
#include "move_types.h"
#include "piece.h"
#include "square.h"
#include "zobrist.h"

/** */
struct Move
{
    enum Square source;
    enum Square target;
    enum Piece piece;
    enum MoveTypes type;
};

/** */
typedef struct Move* Move;

/**
 * 
 * @param result
*/
void move_from_null(Move result);

/**
 *
 * @param result
 * @param value
 * @param board
 * @param table
 * @return
*/
bool move_from_uci_string(
    Move result,
    String value,
    Board board,
    AttackTable table);

/**
 *
 * @param instance
 * @param board
 * @param zobrist
*/
void move_apply(Move instance, Board board, Zobrist zobrist);

/**
 *
 * @param output
 * @param instance
 * @return
*/
void move_write_string(Stream output, Move instance);

/**
 *
 * @param output
 * @param instance
*/
void move_write_uci_string(char buffer[], Move instance);

#endif
