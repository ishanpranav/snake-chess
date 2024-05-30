// transposition_table.h
// Licensed under the MIT license.

// https://www.chessprogramming.org/Transposition_Table

#ifndef TRANSPOSITION_TABLE_96498f09c8eb493589d435e8be4ffa66
#define TRANSPOSITION_TABLE_96498f09c8eb493589d435e8be4ffa66
#include <stdbool.h>
#include "transposition.h"
#include "transposition_table_result.h"
#include "zobrist.h"

/** */
struct TranspositionTable
{
    struct Transposition* items;
    size_t capacity;
    struct Zobrist zobrist;
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
 * @param result
 * @param instance
 * @param hash
 * @param alpha
 * @param beta
 * @param depth
 * @return
*/
bool transposition_table_try_get(
    TranspositionTableResult result,
    TranspositionTable instance,
    uint64_t hash,
    int alpha,
    int beta,
    int depth);

/**
 *
 * @param instance
 * @param hash
 * @param value
 * @param score
 * @param depth
 * @param type
*/
void transposition_table_set(
    TranspositionTable instance,
    uint64_t hash,
    Move value,
    int score,
    int depth,
    NodeType type);

/**
 *
 * @param instance
*/
void finalize_transposition_table(TranspositionTable instance);

#endif
