// xorshift32_random.c
// Copyright (c) 2024 Ishan Pranav
// Licensed under the MIT license.

// Retrieved from https://github.com/ishanpranav/codebook

// https://github.com/ishanpranav/codebook/blob/master/lib/randoms/xorshift32_random.c

#include "random.h"

uint32_t xorshift32_random32(Object instance)
{
    uint32_t* state = instance;
    uint32_t x = *state;

    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;

    return x;
}

uint64_t xorshift32_random64(Object instance)
{
    uint64_t a = xorshift32_random32(instance) & 0xfffful;
    uint64_t b = xorshift32_random32(instance) & 0xfffful;
    uint64_t c = xorshift32_random32(instance) & 0xfffful;
    uint64_t d = xorshift32_random32(instance) & 0xfffful;

    return a | (b << 16) | (c << 32) | (d << 48);
}
