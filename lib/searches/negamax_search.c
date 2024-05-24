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

int negamax_search_alpha_beta(
    Move result,
    Board board,
    AttackTable table,
    Zobrist zobrist,
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
    struct Move optimum;
    struct MoveCollection moves;

    move_from_null(&optimum);
    move_collection(&moves);
    spawn(&moves, board, table);

    for (int i = 0; i < moves.count; i++)
    {
        struct Board clone = *board;

        ply++;

        move_apply(moves.items + i, &clone, zobrist);

        if (check_test_position(&clone, table))
        {
            ply--;

            continue;
        }

        hasLegalMoves = true;

        int score = -negamax_search_alpha_beta(
            result,
            &clone,
            table,
            zobrist,
            -beta,
            -alpha,
            depth - 1);

        ply--;

        if (score >= beta)
        {
            *result = optimum;

            return beta;
        }

        if (score > alpha)
        {
            alpha = score;
            optimum = moves.items[i];
        }
    }

    if (!hasLegalMoves)
    {
        board->color = !board->color;

        bool checked = check_test_position(board, table);

        board->color = !board->color;
        *result = optimum;

        if (checked)
        {
            return INT_MIN + ply;
        }

        return 0;
    }

    *result = optimum;

    return alpha;
}

void negamax_search(
    Move result,
    Board board,
    AttackTable table,
    Zobrist zobrist,
    int depth)
{
    negamax_search_alpha_beta(
        result,
        board,
        table,
        zobrist,
        -INT_MAX,
        INT_MAX,
        depth);
}
