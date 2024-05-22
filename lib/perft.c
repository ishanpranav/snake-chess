// perft.c
// Licensed under the MIT license.

// https://www.chessprogramming.org/Perft

#include "check.h"
#include "spawn.h"

long long perft(Board board, AttackTable table, int depth)
{
    if (!depth)
    {
        return 1;
    }

    long long result = 0;
    struct MoveCollection results;

    results.count = 0;

    spawn_moves(&results, board, table);

    for (int i = 0; i < results.count; i++)
    {
        struct Board clone = *board;

        move_apply(results.items + i, board);

        if (!check_test_position(board, table))
        {
            result += perft(board, table, depth - 1);
        }

        *board = clone;
    }

    return result;
}
