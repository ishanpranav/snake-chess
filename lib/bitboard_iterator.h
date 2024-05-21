// bitboard_iterator.h
// Licensed under the MIT license.

#include "bitboard.h"

/** */
struct BitboardIterator
{
    uint64_t value;
    enum Square current;
};

/** */
typedef struct BitboardIterator* BitboardIterator;

/**
 *
 * @param iterator
 * @param value
*/
void bitboard_begin(BitboardIterator iterator, uint64_t value);

/**
 *
 * @param iterator
 * @param value
*/
void bitboard_next(BitboardIterator iterator);
