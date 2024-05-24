// random.h
// Copyright (c) 2024 Ishan Pranav
// Licensed under the MIT License.

// Retrieved from https://github.com/ishanpranav/codebook

// https://github.com/ishanpranav/codebook/blob/master/lib/random.h

#include <stdint.h>
#include "object.h"

/**
 * Generates a random 32-bit integer using Marsaglia's xorshift32 (exclusive or,
 * 32-bit) algorithm, and returns a value truncated to exactly 32 bits.
 *
 * @param instance the instance.
 * @return A uniformly distributed random 32-bit integer in the interval.
*/
uint32_t xorshift32_random32(Object instance);

/**
 * Generates a random 64-bit integer using multiple calls to Marsaglia's
 * xorshift32 (exclusive or, 32-bit) algorithm, and returns a value aligned to
 * exactly 64 bits.
 *
 * @param instance the instance
 * @return A uniformly distributed random 64-bit integer in the interval.
*/
uint64_t xorshift32_random64(Object instance);
