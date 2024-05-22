// check.h
// Licensed under the MIT license.

#include <stdbool.h>
#include "board.h"
#include "attack_table.h"

/**
 *
 * @param board
 * @param table
 * @param square
 * @param color
*/
bool check_test(Board board, AttackTable table, Square square, Color color);

/**
 *
 * @param board
 * @param table
*/
bool check_test_position(Board board, AttackTable table);
