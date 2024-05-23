// main.c
// Licensed under the MIT license.

#include <stdlib.h>
#include "../lib/attack_table.h"
#include "../lib/board.h"
#include "../lib/move.h"

int main(void)
{
    AttackTable table = malloc(sizeof * table);
    struct Board state;
    struct Move move;

    attack_table(table);
    board_from_fen_string(&state, BOARD_INITIAL);

    char buffer[100];

    printf("move: ");
    scanf("%s", buffer);
    printf("%d\n", move_from_string(&move, buffer, &state, table));
    free(table);

    return 0;
}
