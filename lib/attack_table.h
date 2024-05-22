// attack_table.h
// Licensed under the MIT license.

#ifndef ATTACK_TABLE_6983fe1ab8974ea3a5afeaf19e004d72
#define ATTACK_TABLE_6983fe1ab8974ea3a5afeaf19e004d72
#include <stdint.h>
#include "color.h"
#include "square.h"

/** */
extern const uint64_t ATTACK_TABLE_BISHOP_MAGICS[];

/** */
extern const int ATTACK_TABLE_BISHOP_OCCUPANCY_LENGTHS[];

/** */
extern const uint64_t ATTACK_TABLE_ROOK_MAGICS[];

/** */
extern const int ATTACK_TABLE_ROOK_OCCUPANCY_LENGTHS[];

/** */
struct AttackTable
{
    uint64_t kings[SQUARES];
    uint64_t knights[SQUARES];
    uint64_t pawns[COLORS][SQUARES];
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

#endif
