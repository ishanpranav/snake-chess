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
    struct MoveCollection moves;
    struct Zobrist hash;
    uint32_t state = ZOBRIST_SEED;

    move_collection(&moves);
    spawn(&moves, board, table);
    zobrist(&hash, &state);

    for (int i = 0; i < moves.count; i++)
    {
        struct Board clone = *board;

        move_apply(moves.items + i, &clone, &hash);

        if (!check_test_position(&clone, table))
        {
            result += perft(&clone, table, depth - 1);
        }
    }

    return result;
}
