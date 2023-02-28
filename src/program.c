#include <stdio.h>
#include "attack_table.h"
#include "bitboard.h"
#include "color.h"

int main()
{
    printf("Snake\n");

    struct AttackTable* table = attack_table();

    finalize_attack_table(table);

    return 0;
}
