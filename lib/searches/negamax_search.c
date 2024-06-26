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
#define NEGAMAX_CHECKMATE_VALUE 100000
#define NEGAMAX_CHECKMATE_THRESHOLD 99000

static int negamax_search_alpha_beta(
    SearchResult result,
    Board board,
    AttackTable table,
    TranspositionTable cache,
    int ply,
    int alpha,
    int beta,
    int depth)
{
    if (!depth)
    {
        return evaluation_evaluate_board(board);
    }

    if (ply > result->depth)
    {
        result->depth = ply;
    }

    if (check_test_position(board, table))
    {
        depth++;
    }

    uint64_t hash = board->hash;
    struct TranspositionTableResult entry;

    if (transposition_table_try_get(&entry, cache, hash, alpha, beta, depth))
    {
        result->move = entry.value;

        return entry.score;
    }

    bool hasLegalMoves = false;
    struct Move optimum;
    struct MoveCollection moves;
    NodeType type = NODE_TYPE_ALL_ALPHA;

    move_from_null(&optimum);
    move_collection(&moves);
    spawn(&moves, board, table);
    move_collection_sort(&moves, board, table);

    for (int i = 0; i < moves.count; i++)
    {
        struct Board clone = *board;

        move_apply(moves.items + i, &clone, &cache->zobrist);

        if (check_test_position(&clone, table))
        {
            continue;
        }

        result->nodes++;
        hasLegalMoves = true;

        int score = -negamax_search_alpha_beta(
            result,
            &clone,
            table,
            cache,
            ply + 1,
            -beta,
            -alpha,
            depth - 1);

        if (score >= beta)
        {
            result->move = optimum;

            transposition_table_set(
                cache,
                board->hash,
                &optimum,
                score,
                depth,
                NODE_TYPE_CUT_BETA);

            return beta;
        }

        if (score > alpha)
        {
            alpha = score;
            optimum = moves.items[i];
            type = NODE_TYPE_PRINCIPAL_VARIATION;
        }
    }

    if (!hasLegalMoves)
    {
        board->color = !board->color;

        bool checked = check_test_position(board, table);

        board->color = !board->color;
        result->move = optimum;

        if (checked)
        {
            return -NEGAMAX_CHECKMATE_VALUE + ply;
        }

        return 0;
    }

    result->move = optimum;

    transposition_table_set(cache, board->hash, &optimum, alpha, depth, type);

    return alpha;
}

void negamax_search(
    SearchResult result,
    Board board,
    AttackTable table,
    TranspositionTable cache,
    int depth)
{
    result->nodes = 0;
    result->depth = 0;

    int score = 0;

    for (int currentDepth = 1; currentDepth <= depth; currentDepth++)
    {
        score = negamax_search_alpha_beta(
            result,
            board,
            table,
            cache,
            0,
            -INT_MAX,
            INT_MAX,
            currentDepth);
    }

    result->depth++;
    result->score = score;

    if (score > NEGAMAX_CHECKMATE_THRESHOLD)
    {
        result->mate = NEGAMAX_CHECKMATE_VALUE - score;
    }
    else if (score < -NEGAMAX_CHECKMATE_THRESHOLD)
    {
        result->mate = -NEGAMAX_CHECKMATE_VALUE - score;
    }
    else
    {
        result->mate = 0;
    }
}
