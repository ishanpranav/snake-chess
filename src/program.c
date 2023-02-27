#include <stdio.h>
#include "attacks.h"
#include "bitboard.h"
#include "color.h"

int main()
{
    printf("Snake\n");
    bitboard_print(mask_pawn_attacks(WHITE, G4));

    return 0;
}
