// magic.c
// Licensed under the MIT license.

#include "../ishan/random.h"
#include "magic.h"

uint64_t magic_generate_candidate(uint64_t* state)
{
    return xorshift32_random64(state) &
        xorshift32_random64(state) &
        xorshift32_random64(state);
}
