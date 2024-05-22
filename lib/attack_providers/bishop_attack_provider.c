// bishop_attack_provider.c
// Licensed under the MIT license.

#include "../attack_provider.h"

uint64_t bishop_attack_provider(
    AttackTable table,
    Square square,
    uint64_t obstacles)
{
    obstacles &= table->bishopRelevantOccupancies[square];
    obstacles *= ATTACK_TABLE_BISHOP_MAGICS[square];
    obstacles >>= 64 - ATTACK_TABLE_BISHOP_OCCUPANCY_LENGTHS[square];

    return table->bishops[square][obstacles];
}
