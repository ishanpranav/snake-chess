// move.h
// Licensed under the MIT license.

#include <stdbool.h>
#include "../ishan/stream.h"
#include "attack_table.h"
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
 * @return
*/
bool move_try(Move instance, Board board, AttackTable table);

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
