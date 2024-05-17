// magic.c
// Licensed under the MIT license.

#include "../ishan/random.h"
#include "../lib/sliding.h"

struct Magic
{
    uint64_t occupancies;
    uint64_t attacks;
    uint64_t visitedAttacks;
};

typedef struct Magic* Magic;

static uint64_t magic_generate_candidate(uint64_t* state)
{
    return xorshift32_random64(state) &
        xorshift32_random64(state) &
        xorshift32_random64(state);
}

static uint64_t magic_occupancy(
    int index,
    uint64_t relevantOccupancies,
    int count)
{
    uint64_t result = 0;

    for (int n = 0; n < count; n++)
    {
        Square square = bitboard_first(relevantOccupancies);

        bitboard_clear(relevantOccupancies, square);

        if (index & (1 << n))
        {
            bitboard_set(result, square);
        }
    }

    return result;
}

static uint64_t magic_generate_bishop(
    Magic magic,
    Square square,
    int count,
    int iterations)
{
    int capacity = 1 << count;
    uint64_t relevantOccupancies =
        sliding_generate_bishop_relevant_occupancies(square);
    Magic table = malloc(4096 * sizeof * table);

    for (int index = 0; index < capacity; index++)
    {
        Magic magic = table + index;
        uint64_t occupancies = magic_occupancy(
            index,
            count,
            relevantOccupancies);

        magic->occupancies = occupancies;
        magic->attacks = sliding_generate_bishop_attacks(square, occupancies);
    }

    for (int i = 0; i < iterations; i++)
    {

    }

    return 0;
}

static uint64_t magic_generate_rook(Square square, int count)
{
    return 0;
}

int main(void)
{
    return 0;
}
