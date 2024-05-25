// evaluation.h
// Licensed under the MIT license.

#include "board.h"
#include "move.h"

/**
 *
 * @param board
 * @return
*/
int evaluation_evaluate_board(Board board);

/**
 *
 * @param move
 * @param board
 * @return
*/
int evaluation_evaluate_move(Move move, Board board);
