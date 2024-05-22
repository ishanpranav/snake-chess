// attack_provider.h
// Licensed under the MIT license.

#include "attack_table.h"

/** */
typedef uint64_t(*AttackProvider)(
    AttackTable table,
    Square square,
    uint64_t obstacles);

/**
 *
 * @param table
 * @param square
 * @param obstacles
*/
uint64_t knight_attack_provider(
    AttackTable table,
    Square square,
    uint64_t obstacles);

/**
 *
 * @param table
 * @param square
 * @param obstacles
*/
uint64_t bishop_attack_provider(
    AttackTable table,
    Square square,
    uint64_t obstacles);

/**
 *
 * @param table
 * @param square
 * @param obstacles
*/
uint64_t rook_attack_provider(
    AttackTable table,
    Square square,
    uint64_t obstacles);

/**
 *
 * @param table
 * @param square
 * @param obstacles
*/
uint64_t queen_attack_provider(
    AttackTable table,
    Square square,
    uint64_t obstacles);

/**
 *
 * @param table
 * @param square
 * @param obstacles
*/
uint64_t king_attack_provider(
    AttackTable table,
    Square square,
    uint64_t obstacles);
