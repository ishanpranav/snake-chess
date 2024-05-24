// transposition_table.h
// Licensed under the MIT license.

// https://www.chessprogramming.org/Transposition_Table

#include <stdbool.h>
#include "transposition.h"

/** */
struct TranspositionTable
{
    struct Transposition* items;
    size_t capacity;
};

/** */
typedef struct TranspositionTable* TranspositionTable;

/**
 *
 * @param instance
 * @param capacity
*/
void transposition_table(TranspositionTable instance, size_t capacity);

/**
 *
 * @param instance
 * @param hash
 * @param alpha
 * @param beta
 * @param depth
 * @param result
 * @return
*/
bool transposition_table_try_get(
    TranspositionTable instance,
    uint64_t hash,
    int alpha,
    int beta,
    int depth,
    int* result);
