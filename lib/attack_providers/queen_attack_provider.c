// queen_attack_provider.c
// Licensed under the MIT license.

#include "../attack_provider.h"

uint64_t queen_attack_provider(
    AttackTable table,
    Square square,
    uint64_t obstacles)
{
    return
        bishop_attack_provider(table, square, obstacles) |
        rook_attack_provider(table, square, obstacles);
}
