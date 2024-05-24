// transposition_table_result.c
// Licensed under the MIT license.

#include "move.h"

/** */
struct TranspositionTableResult
{
    struct Move value;
    int score;
};

/** */
typedef struct TranspositionTableResult* TranspositionTableResult;
