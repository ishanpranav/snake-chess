#include <stdint.h>
#include <stdbool.h>
#include "square.h"

/**
 *
 */
unsigned long long bitboard(enum Square square);

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
