// xorshift32_random.c
// Copyright (c) 2024 Ishan Pranav
// Licensed under the MIT License.

// Retrieved from https://github.com/ishanpranav/codebook/
// See also https://en.wikipedia.org/wiki/Xorshift
// Journal of Statistical Software, https://www.jstatsoft.org/article/view/v008i14

// https://github.com/ishanpranav/codebook/blob/0d73343eb7fdd4ae962346d8b86317d68f1b49b1/lib/randoms/xorshift32_random.c

#include "../random.h"

long long xorshift32_random(Object instance, long long max)
{
    return xorshift32_random32(instance) % max;
}

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
