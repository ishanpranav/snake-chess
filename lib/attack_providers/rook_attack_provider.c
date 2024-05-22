// rook_attack_provider.c
// Licensed under the MIT license.

#include "../attack_provider.h"

uint64_t rook_attack_provider(
    AttackTable table,
    Square square,
    uint64_t obstacles)
{
    obstacles &= table->rookRelevantOccupancies[square];
    obstacles *= ATTACK_TABLE_ROOK_MAGICS[square];
    obstacles >>= 64 - ATTACK_TABLE_ROOK_OCCUPANCY_LENGTHS[square];

    return table->rooks[square][obstacles];
}
