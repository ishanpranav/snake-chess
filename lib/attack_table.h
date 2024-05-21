// attack_table.h
// Licensed under the MIT license.

#include <stdint.h>
#include "color.h"
#include "square.h"

/** */
struct AttackTable
{
    uint64_t pawns[COLORS][SQUARES];
    uint64_t knights[SQUARES];
    uint64_t kings[SQUARES];
    uint64_t bishops[SQUARES][512];
    uint64_t rooks[SQUARES][4096];
    uint64_t bishopRelevantOccupancies[SQUARES];
    uint64_t rookRelevantOccupancies[SQUARES];
};

/** */
typedef struct AttackTable* AttackTable;

/**
 *
 * @param instance
*/
void attack_table(AttackTable instance);

/**
 *
 * @param instance
 * @param square
 * @param obstacles
 * @return
*/
uint64_t attack_table_get_bishop(
    AttackTable instance,
    Square square,
    uint64_t obstacles);

/**
 *
 * @param instance
 * @param square
 * @param obstacles
 * @return
*/
uint64_t attack_table_get_rook(
    AttackTable instance,
    Square square,
    uint64_t obstacles);
