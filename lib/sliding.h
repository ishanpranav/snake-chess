// sliding.h
// Licensed under the MIT license.

#include <stdint.h>
#include "square.h"

/**
 *
 * @param square
 * @return
*/
uint64_t sliding_generate_bishop_relevant_occupancies(Square square);

/**
 *
 * @param square
 * @return
*/
uint64_t sliding_generate_rook_relevant_occupancies(Square square);

/**
 *
 * @param square
 * @param obstacles
 * @return
*/
uint64_t sliding_generate_bishop_attacks(Square square, uint64_t obstacles);

/**
 *
 * @param square
 * @param obstacles
 * @return
*/
uint64_t sliding_generate_rook_attacks(Square square, uint64_t obstacles);
