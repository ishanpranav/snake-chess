// generator.c
// Licensed under the MIT license.

#include <stdbool.h>
#include <stdlib.h>
#include "../lib/bitboard.h"
#include "../lib/file.h"
#include "../lib/move.h"
#include "../lib/spawner.h"

static void make_move(Board board, Move move)
{
    board->pieces[move->piece] &= ~bitboard(move->source);
    board->pieces[move->piece] |= bitboard(move->target);

    Piece enemyBegin = 0;
    uint64_t target = bitboard(move->target);

    if (!board->color)
    {
        enemyBegin += PIECE_BLACK_PAWN;
    }

    if (move->type & MOVE_TYPES_CAPTURE)
    {
        Piece enemyEnd = enemyBegin + PIECE_KING;

        for (Piece piece = enemyBegin; piece <= enemyEnd; piece++)
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
        Piece friendOffset = 0;

        if (board->color)
        {
            friendOffset += PIECE_BLACK_PAWN;
        }

        board->pieces[friendOffset + PIECE_PAWN] &= ~target;

        if (move->type & MOVE_TYPES_KNIGHT)
        {
            board->pieces[friendOffset + PIECE_KNIGHT] |= target;
        }
        else if (move->type & MOVE_TYPES_BISHOP)
        {
            board->pieces[friendOffset + PIECE_BISHOP] |= target;
        }
        else if (move->type & MOVE_TYPES_ROOK)
        {
            board->pieces[friendOffset + PIECE_ROOK] |= target;
        }
        else if (move->type & MOVE_TYPES_QUEEN)
        {
            board->pieces[friendOffset + PIECE_QUEEN] |= target;
        }
    }

    if (move->type & MOVE_TYPES_EN_PASSANT)
    {
        int target = move->target;

        if (board->color)
        {
            target -= FILES;
        }
        else
        {
            target += FILES;
        }

        board->pieces[enemyBegin + PIECE_PAWN] &= ~bitboard(target);
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
        "r3k2r/p11pqpb1/bn2pnp1/2pPN3/Pp2P3/2N2Q1p/1PPBBPPP/R3K2R b KQkq a3 0 1");
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
