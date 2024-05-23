// main.c
// Licensed under the MIT license.

#include <stdlib.h>
#include <string.h>
#include "../lib/uci.h"

#include "../lib/spawn.h"

int main(void)
{
    Uci state = malloc(sizeof * state);

    euler_assert(state);
    uci(state, stdout);
    
    char buffer[16384];

    while (fgets(buffer, sizeof buffer, stdin) && uci_evaluate(state, buffer))
    {
        fflush(state->output);
        board_write_string(state->output, &state->board, ENCODING_ASCII);
    }

    free(state);

    // board_from_fen_string(&state->board, BOARD_INITIAL);

    // struct MoveCollection moves;

    // move_collection(&moves);
    // spawn(&moves, &state->board, &state->table);

    // for (int i = 0; i < moves.count; i++)
    // {
    //     move_write_string(stdout, moves.items + i);
    //     printf("\n");
    // }
    return 0;
}
