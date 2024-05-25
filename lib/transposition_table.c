// transposition_table.c
// Licensed under the MIT license.

#include <stdlib.h>
#include "transposition_table.h"
#define transposition_table_find(instance, hash) \
    ((instance)->items + ((hash) % (instance)->capacity))

void transposition_table(TranspositionTable instance, size_t capacity)
{
    uint32_t state = 1804289383;

    zobrist(&instance->zobrist, &state);

    instance->items = calloc(capacity, sizeof * instance->items);
    instance->capacity = capacity;
}

bool transposition_table_try_get(
    TranspositionTableResult result,
    TranspositionTable instance,
    uint64_t hash,
    int alpha,
    int beta,
    int depth)
{
    Transposition entry = transposition_table_find(instance, hash);

    if (entry->hash != hash)
    {
        return false;
    }

    if (entry->depth < depth)
    {
        return false;
    }

    result->value = entry->value;

    switch (entry->type)
    {
    case NODE_TYPE_PRINCIPAL_VARIATION:
        result->score = entry->score;

        return true;

    case NODE_TYPE_CUT_BETA:
        result->score = beta;

        return entry->score >= beta;

    case NODE_TYPE_ALL_ALPHA:
        result->score = beta;

        return entry->score <= alpha;

    default: return false;
    }
}

void transposition_table_set(
    TranspositionTable instance,
    uint64_t hash,
    Move value,
    int score,
    int depth,
    NodeType type)
{
    if (value->source == value->target)
    {
        return;
    }

    Transposition entry = transposition_table_find(instance, hash);

    entry->hash = hash;
    entry->value = *value;
    entry->score = score;
    entry->depth = depth;
    entry->type = type;
}
