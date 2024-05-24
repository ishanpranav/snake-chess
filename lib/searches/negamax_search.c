// negamax_search.c
// Licensed under the MIT license.

// https://en.wikipedia.org/wiki/Negamax
// https://www.chessprogramming.org/Negamax
// https://www.chessprogramming.org/Unmake_Move
// https://www.chessprogramming.org/Alpha-Beta

#include <limits.h>
#include "../check.h"
#include "../evaluation.h"
#include "../search.h"
#include "../spawn.h"

int negamax_search_impl(
    Board board,
    AttackTable table,
    int alpha,
    int beta,
    int depth)
{
    if (!depth)
    {
        return evaluation(board);
    }

    int ply = 0;
    bool hasLegalMoves = false;
    struct MoveCollection moves;

    move_collection(&moves);
    spawn(&moves, board, table);

    for (int i = 0; i < moves.count; i++)
    {
        struct Board clone = *board;

        ply++;

        move_apply(moves.items + i, &clone);

        if (check_test_position(&clone, table))
        {
            ply--;

            continue;
        }
        
        hasLegalMoves = true;

        int score = -negamax_search_impl(
            &clone,
            table,
            -beta,
            -alpha,
            depth - 1);

        ply--;

        if (score >= beta)
        {
            return beta;
        }

        if (score > alpha)
        {
            alpha = score;
        }
    }

    if (!hasLegalMoves)
    {
        board->color = !board->color;

        bool checked = check_test_position(board, table);

        board->color = !board->color;

        if (checked)
        {
            return INT_MIN + ply;
        }

        return 0;
    }

    return alpha;
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
            -INT_MAX,
            INT_MAX,
            depth);

        if (score > max)
        {
            max = score;
            *result = moves.items[i];
        }
    }
}
