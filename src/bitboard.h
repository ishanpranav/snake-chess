#include <stdbool.h>
#include "square.h"

/**
 *
 */
bool bitboard_get(unsigned long long this, enum Square square);

/**
 *
 */
void bitboard_set(unsigned long long *this, enum Square square);

/**
 *
 */
void bitboard_reset(unsigned long long *this, enum Square square);
