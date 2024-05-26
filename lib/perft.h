// perft.h
// Licensed under the MIT license.

#include "attack_table.h"
#include "board.h"
#include "zobrist.h"

/**
 *
 * @param depth
 * @return
*/
long long perft(Board board, AttackTable table, Zobrist zobrist, int depth);
