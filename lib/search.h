// search.h
// Licensed under the MIT license.

#include "board.h"
#include "attack_table.h"
#include "search_result.h"
#include "transposition_table.h"

/**
 *
 * @param
*/
void negamax_search(
    SearchResult result,
    Board board,
    AttackTable table,
    TranspositionTable cache,
    int depth);
