// perft.h
// Licensed under the MIT license.

#include "attack_table.h"
#include "board.h"

/**
 *
 * @param depth
 * @return
*/
long long perft(Board board, AttackTable table, Zobrist zobrist, int depth);
