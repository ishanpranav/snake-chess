// bitboard_iterator.c
// Licensed under the MIT license.

#include "bitboard_iterator.h"

void bitboard_begin(BitboardIterator iterator, uint64_t value)
{
    iterator->value = value;
    iterator->current = bitboard_first(value);
}

void bitboard_next(BitboardIterator iterator)
{
    iterator->value &= ~bitboard(iterator->current);
    iterator->current = bitboard_first(iterator->value);
}
