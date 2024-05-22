// move.h
// Licensed under the MIT license.

#include <stdbool.h>
#include "../ishan/stream.h"
#include "piece.h"
#include "square.h"

/** */
struct Move
{
    enum Square source;
    enum Square target;
    enum Piece piece;
    enum Piece promotion;
    bool capture;
    bool doublePush;
    bool enPassant;
    bool castle;
};

/** */
typedef struct Move* Move;

/**
 *
 * @param output
 * @param value
 * @return
*/
void move_write_string(Stream output, Move value);

/**
 *
 * @param output
 * @param value
*/
void move_write_uci_string(Stream output, Move value);
