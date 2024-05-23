// search.h
// Licensed under the MIT license.

#include "board.h"
#include "attack_table.h"
#include "move.h"

/**
 * 
 * @param 
*/
void search(Move result, Board board, AttackTable table, int depth);

/**
 * 
 * @param 
*/
void negamax_search(Move result, Board board, AttackTable table, int depth);
