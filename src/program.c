#include <stdio.h>
#include "bitboard.h"

int main()
{
    unsigned long long bitboard = 4ull;
    
    printf("Snake\n");
    bitboard_print(bitboard);

    return 0;
}
