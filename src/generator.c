// generator.c
// Licensed under the MIT license.

#include <stdbool.h>
#include <stdlib.h>
#include "../lib/bitboard.h"
#include "../lib/file.h"
#include "../lib/move.h"
#include "../lib/spawner.h"

static void relocate(Board board, Piece piece, uint64_t source, uint64_t target)
{
    board->pieces[piece] &= ~source;
    board->pieces[piece] |= target;
}

static void make_move(Board board, Move move)
{
    uint64_t source = bitboard(move->source);
    uint64_t target = bitboard(move->target);

    relocate(board, move->piece, source, target);

    int direction;
    Piece enemyBegin;
    Piece friendBegin;

    if (board->color)
    {
        direction = -1;
        enemyBegin = PIECE_WHITE_PAWN;
        friendBegin = PIECE_BLACK_PAWN;
    }
    else
    {
        direction = 1;
        enemyBegin = PIECE_BLACK_PAWN;
        friendBegin = PIECE_WHITE_PAWN;
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
        board->pieces[friendBegin + PIECE_PAWN] &= ~target;

        if (move->type & MOVE_TYPES_KNIGHT)
        {
            board->pieces[friendBegin + PIECE_KNIGHT] |= target;
        }
        else if (move->type & MOVE_TYPES_BISHOP)
        {
            board->pieces[friendBegin + PIECE_BISHOP] |= target;
        }
        else if (move->type & MOVE_TYPES_ROOK)
        {
            board->pieces[friendBegin + PIECE_ROOK] |= target;
        }
        else if (move->type & MOVE_TYPES_QUEEN)
        {
            board->pieces[friendBegin + PIECE_QUEEN] |= target;
        }
    }

    if (move->type & MOVE_TYPES_EN_PASSANT)
    {
        Square enPassantTarget = move->target + direction * FILES;

        board->pieces[enemyBegin + PIECE_PAWN] &= ~bitboard(enPassantTarget);
    }

    board->enPassant = SQUARES;

    if (move->type & MOVE_TYPES_DOUBLE_PUSH)
    {
        board->enPassant = move->target + direction * FILES;
    }

    if (move->type & MOVE_TYPES_CASTLE_KINGSIDE)
    {
        relocate(
            board, 
            friendBegin + PIECE_ROOK, 
            bitboard(move->source + 3), 
            bitboard(move->source + 1));
    }

    if (move->type & MOVE_TYPES_CASTLE_QUEENSIDE)
    {
        relocate(
            board,
            friendBegin + PIECE_ROOK,
            bitboard(move->source - 4),
            bitboard(move->source - 1));
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
        "r3k2r/p11pqpb1/bn2pnp1/2pPN3/Pp2P3/2N2Q1p/1PPBBPPP/R3K2R w KQkq a3 0 1");
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
