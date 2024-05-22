// snake_perft.c
// Licensed under the MIT liense.

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/perft.h"

int main(int count, String args[])
{
    if (count < 2)
    {
        printf("usage: ./snake_perft <depth> <position>\n");

        return 1;
    }

    int depth = strtol(args[1], NULL, 10);

    if (!depth)
    {
        printf("usage: bad depth argument\n");

        return 1;
    }

    String position;

    if (count > 2)
    {
        position = args[2];
    }
    else
    {
        position = BOARD_INITIAL;
    }

    AttackTable table = malloc(sizeof * table);
    struct Board state;

    attack_table(table);
    board_from_fen_string(&state, position);
    board_write_string(stdout, &state, ENCODING_STANDARD);

    clock_t start = clock();
    long long result = perft(&state, table, depth);
    double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    double speed = result / elapsed;

    printf(
        "elapsed: %lf s\n"
        "speed: %0.lf positions/s\n"
        "result: %lld positions\n",
        elapsed, speed, result);

    free(table);

    return 0;
}
