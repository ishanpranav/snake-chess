#include <stdio.h>
#include "attack_table.h"
#include "color.h"

int main()
{
    printf("Snake\n");

    AttackTable table = attack_table();

    finalize_attack_table(table);

    return 0;
}
