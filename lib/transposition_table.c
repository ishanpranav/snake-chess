// transposition_table.c
// Licensed under the MIT license.

#include <stdlib.h>
#include "transposition_table.h"

void transposition_table(TranspositionTable instance, size_t capacity)
{
    instance->items = calloc(capacity, sizeof * instance->items);
    instance->capacity = capacity;
}

bool transposition_table_try_get(
    TranspositionTable instance,
    uint64_t hash,
    int alpha,
    int beta,
    int depth,
    int* result)
{
    Transposition entry = instance->items + (hash % instance->capacity);

    if (entry->hash != hash)
    {
        return false;
    }

    if (entry->depth < depth)
    {
        return false;
    }

    switch (entry->type)
    {
    case NODE_TYPE_PRINCIPAL_VARIATION:
        *result = entry->score;

        return true;

    case NODE_TYPE_CUT_BETA:
        *result = beta;

        return entry->score >= beta;

    case NODE_TYPE_ALL_ALPHA:
        *result = alpha;

        return entry->score <= alpha;

    default: return false;
    }
}

void transposition_table_set(int score, int depth, NodeType type)
{

}
