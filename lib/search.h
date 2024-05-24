// search.h
// Licensed under the MIT license.

#include "board.h"
#include "attack_table.h"
#include "move.h"
#include "zobrist.h"

/**
 * 
 * @param 
*/
void negamax_search(
    Move result, 
    Board board, 
    AttackTable table,
    Zobrist zobrist,
    int depth);
