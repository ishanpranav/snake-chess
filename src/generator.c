// generator.c
// Licensed under the MIT license.

#include <stdbool.h>
#include <stdlib.h>
#include "../lib/bitboard.h"
#include "../lib/move.h"
#include "../lib/spawner.h"

static void make_move(Board board, Move move)
{
    struct Board clone;

    board_copy(&clone, board);

    clone.pieces[move->piece] &= ~bitboard(move->source);
    clone.pieces[move->piece] |= bitboard(move->target);
}

int main(void)
{
    AttackTable a = malloc(sizeof * a);
    struct List moves;

    euler_ok(list(&moves, sizeof(struct Move), 0));

    attack_table(a);

    struct Board b;

    board_from_fen_string(
        &b,
        "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    spawner_generate_moves(&moves, &b, a);
    free(a);
    board_write_string(stdout, &b, ENCODING_UNICODE);

    Move begin = moves.items;
    Move end = begin + moves.count;

    for (Move move = begin; move < end; move++)
    {
        // make_move(&b, move);
        move_write_string(stdout, move);
        fprintf(stdout, "\n");
        // board_write_string(stdout, &b, ENCODING_UNICODE);
        // getchar();
    }

    finalize_list(&moves);

    return 0;
}
