// perft.c
// Licensed under the MIT license.

// https://www.chessprogramming.org/Perft

#include "move.h"
#include "check.h"
#include "spawn.h"

long long perft(Board board, AttackTable table, int depth)
{
    if (!depth)
    {
        return 1;
    }

    long long result = 0;
    struct List results;

    euler_ok(list(&results, sizeof(struct Move), 0));

    spawn_moves(&results, board, table);

    Move begin = results.items;
    Move end = begin + results.count;

    for (Move move = begin; move < end; move++)
    {
        struct Board clone = *board;

        move_apply(move, board);

        if (check_test_position(board, table))
        {
            *board = clone;

            continue;
        }

        result += perft(board, table, depth - 1);
        *board = clone;
    }

    finalize_list(&results);

    return result;
}
