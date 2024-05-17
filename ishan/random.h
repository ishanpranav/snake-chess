// random.h
// Copyright (c) 2024 Ishan Pranav
// Licensed under the MIT License.

// Retrieved from https://github.com/ishanpranav/codebook/

// https://github.com/ishanpranav/codebook/blob/053e69a1a3463bba30b258cecf3fa1b7b18ed45d/lib/random.h

#include <stdint.h>
#include "object.h"

/** Defines a random number generator. */
typedef long long (*Random)(void* instance, long long max);

/**
 * Generates a random integer in the interval [0, `max`] using Marsaglia's
 * xorshift32 (exclusive or, 32-bit) algorithm.
 *
 * @param instance the instance.
 * @param max      the exclusive upper bound of the generated integer.
 * @return A random integer in the interval [0, `max`]. Only the least 32 bits
 *         of this value are necessarily uniformly distributed.
*/
long long xorshift32_random(Object instance, long long max);

/**
 * Generates a random 32-bit integer in the interval [0, `max`] using
 * Marsaglia's xorshift32 (exclusive or, 32-bit) algorithm.
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
