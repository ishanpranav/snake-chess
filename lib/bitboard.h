// bitboard.h
// Licensed under the MIT license.

#include <stdint.h>
#include <stdio.h>
#define BITBOARD_NOT_FILE_A 0xfefefefefefefefeull
#define BITBOARD_NOT_FILE_H 0x7f7f7f7f7f7f7f7full
#define BITBOARD_NOT_FILES_A_OR_B 0xfcfcfcfcfcfcfcfcull
#define BITBOARD_NOT_FILES_H_OR_G 0x3f3f3f3f3f3f3f3full
#define bitboard_get(value, square) (value & (1ull << square))
#define bitboard_set(value, square) (value |= (1ull << square))
#define bitboard_toggle(value, square) (value ^= (1ull << square))
#define bitboard_clear(value, square) \
    (bitboard_get(value, square) ? bitboard_toggle(value, square) : 0)

/**
 *
 * @param output
 * @param value
*/
void bitboard_write_string(FILE* output, uint64_t value);
