// perft.c
// Licensed under the MIT license.

// https://www.chessprogramming.org/Perft

#include "check.h"
#include "perft.h"
#include "spawn.h"

long long perft(Board board, AttackTable table, Zobrist zobrist, int depth)
{
    if (!depth)
    {
        return 1;
    }

    long long result = 0;
    struct MoveCollection moves;

    move_collection(&moves);
    spawn(&moves, board, table);

    for (int i = 0; i < moves.count; i++)
    {
        struct Board clone = *board;

        move_apply(moves.items + i, &clone, zobrist);

        if (!check_test_position(&clone, table))
        {
            result += perft(&clone, table, zobrist, depth - 1);
        }
    }

    return result;
}
