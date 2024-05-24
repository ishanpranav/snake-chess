// main.c
// Licensed under the MIT license.

#include <stdlib.h>
#include <string.h>
#include "../lib/uci.h"

#include <inttypes.h>

int main(void)
{
    Uci state = malloc(sizeof *state);

    euler_assert(state);
    uci(state, stdout);

    char buffer[16384];

    while (fgets(buffer, sizeof buffer, stdin) && uci_evaluate(state, buffer))
    {
        printf("0x%" PRIx64 "\n", state->board.hash);
        board_rehash(&state->board, &state->zobrist);
        printf("0x%" PRIx64 "\n", state->board.hash);
        fflush(state->output);
    }

    free(state);

    return 0;
}
