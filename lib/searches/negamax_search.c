// negamax_search.c
// Licensed under the MIT license.

// https://en.wikipedia.org/wiki/Negamax
// https://www.chessprogramming.org/Negamax
// https://www.chessprogramming.org/Unmake_Move

#include <limits.h>
#include "../check.h"
#include "../evaluation.h"
#include "../search.h"
#include "../spawn.h"

int negamax_search_impl(
    Board board,
    AttackTable table,
    int depth)
{
    if (!depth)
    {
        return evaluation(board);
    }

    int max = INT_MIN;
    struct MoveCollection moves;

    move_collection(&moves);
    spawn(&moves, board, table);

    for (int i = 0; i < moves.count; i++)
    {
        struct Board clone = *board;

        move_apply(moves.items + i, &clone);

        if (check_test_position(&clone, table))
        {
            continue;
        }

        int score = -negamax_search_impl(
            &clone,
            table,
            depth - 1);

        if (score > max)
        {
            max = score;
        }
    }

    return max;
}

void negamax_search(Move result, Board board, AttackTable table, int depth)
{
    int max = INT_MIN;
    struct MoveCollection moves;

    move_from_null(result);
    move_collection(&moves);
    spawn(&moves, board, table);

    for (int i = 0; i < moves.count; i++)
    {
        struct Board clone = *board;

        move_apply(moves.items + i, &clone);

        if (check_test_position(&clone, table))
        {
            continue;
        }

        int score = -negamax_search_impl(
            &clone,
            table,
            depth);

        if (score > max)
        {
            max = score;
            *result = moves.items[i];
        }
    }
}
