// generator.c
// Licensed under the MIT license.

#include <stdbool.h>
#include <stdlib.h>
#include "../lib/bitboard.h"
#include "../lib/move.h"
#include "../lib/spawner.h"

static void make_move(Board board, Move move)
{
    board->pieces[move->piece] &= ~bitboard(move->source);
    board->pieces[move->piece] |= bitboard(move->target);

    uint64_t target = bitboard(move->target);

    if (move->type & MOVE_TYPES_CAPTURE)
    {
        Piece begin = 0;

        if (!board->color)
        {
            begin += PIECE_BLACK_PAWN;
        }

        Piece end = begin + PIECE_KING;

        for (Piece piece = begin; piece <= end; piece++)
        {
            if (board->pieces[piece] & target)
            {
                board->pieces[piece] &= ~target;

                break;
            }
        }
    }

    if (move->type & MOVE_TYPES_PROMOTION)
    {
        Piece begin = 0;

        if (board->color)
        {
            begin += PIECE_BLACK_PAWN;
        }

        board->pieces[begin + PIECE_PAWN] &= ~target;

        if (move->type & MOVE_TYPES_KNIGHT)
        {
            board->pieces[begin + PIECE_KNIGHT] |= target;
        }
        else if (move->type & MOVE_TYPES_BISHOP)
        {
            board->pieces[begin + PIECE_BISHOP] |= target;
        }
        else if (move->type & MOVE_TYPES_ROOK)
        {
            board->pieces[begin + PIECE_ROOK] |= target;
        }
        else if (move->type & MOVE_TYPES_QUEEN)
        {
            board->pieces[begin + PIECE_QUEEN] |= target;
        }
    }
}

int main(void)
{
    AttackTable a = malloc(sizeof *a);
    struct List moves;

    euler_ok(list(&moves, sizeof(struct Move), 0));

    attack_table(a);

    struct Board b;

    board_from_fen_string(
        &b,
        "r3k2r/p1pPqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K11R b KQkq - 0 1");
    spawner_generate_moves(&moves, &b, a);
    free(a);
    board_write_string(stdout, &b, ENCODING_UNICODE);

    Move begin = moves.items;
    Move end = begin + moves.count;

    for (Move move = begin; move < end; move++)
    {
        struct Board clone = b;

        make_move(&b, move);
        move_write_string(stdout, move);
        fprintf(stdout, "\n");
        board_write_string(stdout, &b, ENCODING_UNICODE);
        getchar();

        b = clone;
    }

    finalize_list(&moves);

    return 0;
}
