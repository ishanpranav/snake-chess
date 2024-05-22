// generator.c
// Licensed under the MIT license.

#include <stdbool.h>
#include <stdlib.h>
#include "../lib/file.h"
#include "../lib/move.h"
#include "../lib/spawn.h"

int main(void)
{
    AttackTable a = malloc(sizeof * a);
    struct List moves;

    euler_ok(list(&moves, sizeof(struct Move), 0));

    attack_table(a);

    struct Board b;

    board_from_fen_string(
        &b,
        "r3k2r/p1ppQpb1/1n2pnp1/3PN3/1p2P3/2N2Q1p/PPPBqPPP/R3K2R b KQkq - 0 1");
    spawn_moves(&moves, &b, a);
    board_write_string(stdout, &b, ENCODING_UNICODE);

    Move begin = moves.items;
    Move end = begin + moves.count;

    for (Move move = begin; move < end; move++)
    {
        struct Board clone = b;

        if (!move_try(move, &b, a))
        {
            continue;
        }

        move_write_string(stdout, move);
        fprintf(stdout, "\n");
        board_write_string(stdout, &b, ENCODING_UNICODE);
        getchar();

        b = clone;
    }

    free(a);
    finalize_list(&moves);

    return 0;
}
