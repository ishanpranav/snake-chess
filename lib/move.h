// move.h
// Licensed under the MIT license.

#include "../ishan/stream.h"
#include "board.h"
#include "move_types.h"
#include "piece.h"
#include "square.h"

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
 * @param instance
 * @param board
 * @param table
*/
void move_apply(Move instance, Board board);

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
void move_write_uci_string(Stream output, Move instance);
