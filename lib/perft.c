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

    if (depth == 1)
    {
        return results.count;
    }

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

    return result;
}
