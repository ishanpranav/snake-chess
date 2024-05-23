// main.c
// Licensed under the MIT license.

#include <stdlib.h>
#include <string.h>
#include "../lib/attack_table.h"
#include "../lib/board.h"
#include "../lib/move.h"
#include "../lib/uci.h"

int main(void)
{
    AttackTable table = malloc(sizeof * table);
    struct Board state;

    attack_table(table);
    board_from_fen_string(&state, BOARD_INITIAL);

    char buffer[16384];

    do
    {
        memset(buffer, 0, sizeof buffer);

        if (!fgets(buffer, sizeof buffer, stdin) || buffer[0] == '\n')
        {
            continue;
        }

    } while (uci_evaluate(stdout, buffer));

    return 0;
}
