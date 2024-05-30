// search_result.h
// Licensed under the MIT license.

#include "move.h"

/** */
struct SearchResult
{
    struct Move move;
    long nodes;
    int score;
    int depth;
    int mate;
};

/** */
typedef struct SearchResult* SearchResult;
