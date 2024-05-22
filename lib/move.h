// move.h
// Licensed under the MIT license.

#include <stdbool.h>
#include "../ishan/stream.h"
#include "move_type.h"
#include "piece.h"
#include "square.h"

/** */
struct Move
{
    enum Square source;
    enum Square target;
    enum Piece piece;
    enum Piece promotion;
    enum MoveType type;
};

/** */
typedef struct Move* Move;

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
