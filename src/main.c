// main.c
// Licensed under the MIT license.

#include <stdlib.h>
#include "../lib/attack_table.h"
#include "../lib/board.h"

int main(void)
{
    AttackTable table = malloc(sizeof * table);

    attack_table(table);



    free(table);

    return 0;
}
