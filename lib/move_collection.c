// move_collection.c
// Licensed under the MIT license.

#include <string.h>
#include "../ishan/object.h"
#include "evaluation.h"
#include "move_collection.h"
#include "square.h"

static int scores[SQUARES][SQUARES];

void move_collection(MoveCollection instance)
{
    instance->count = 0;
}

void move_collection_add(MoveCollection instance, Move item)
{
    instance->items[instance->count] = *item;
    instance->count++;
}

static int move_collection_compare_item(Object left, Object right)
{
    const struct Move* p = left;
    const struct Move* q = right;

    if (p->source == q->source && p->target == q->target)
    {
        return 0;
    }

    if (p->source == SQUARES || p->target == SQUARES)
    {
        return 1;
    }

    if (q->source == SQUARES || q->target == SQUARES)
    {
        return -1;
    }

    return scores[q->source][q->target] - scores[p->source][p->target];
}

void move_collection_sort(
    MoveCollection instance,
    Board board,
    AttackTable table)
{
    memset(scores, 0, sizeof scores);

    for (int i = 0; i < instance->count; i++)
    {
        Move move = instance->items + i;

        scores[move->source][move->target] =
            evaluation_evaluate_move(move, board, table);
    }

    qsort(
        instance->items,
        instance->count,
        sizeof * instance->items,
        move_collection_compare_item);
}
