// king_attack_provider.c
// Licensed under the MIT license.

#include "../attack_provider.h"

uint64_t king_attack_provider(
    AttackTable table,
    Square square,
    EULER_UNUSED uint64_t obstacles)
{
    return table->kings[square];
}
