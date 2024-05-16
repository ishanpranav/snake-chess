// bitboard.h
// Licensed under the MIT license.

#include <stdint.h>
#include <stdio.h>
#define bitboard_get(value, square) (value & (1ull << square))
#define bitboard_set(value, square) (value |= (1ull << square))
#define bitboard_toggle(value, square) (value ^= (1ull << square))
#define bitboard_clear(value, square) \
    (bitboard_get(value, square) ? bitboard_toggle(value, square) : 0)

/**s
 *
 * @param output
 * @param value
*/
void bitboard_write_string(FILE* output, uint64_t value);
