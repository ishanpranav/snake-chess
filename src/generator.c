// generator.c
// Licensed under the MIT license.

#include <stdbool.h>
#include <stdlib.h>
#include "../lib/attack_table.h"
#include "../lib/bitboard_iterator.h"
#include "../lib/board.h"
#include "../lib/file.h"
#include "../lib/rank.h"

static bool is_square_attacked(
    Board board,
    AttackTable attacks,
    Square square,
    Color color)
{
    if ((attacks->kings[square] & board_get_kings(board, color)) ||
        (attacks->knights[square] & board_get_knights(board, color)) ||
        (attacks->pawns[!color][square] & board_get_pawns(board, color)))
    {
        return true;
    }

    uint64_t bishopAttacks = attack_table_get_bishop(
        attacks,
        square,
        board->squares);

    if (bishopAttacks & board_get_bishops(board, color))
    {
        return true;
    }

    uint64_t rookAttacks = attack_table_get_rook(
        attacks,
        square,
        board->squares);

    if (rookAttacks & board_get_rooks(board, color))
    {
        return true;
    }

    return (bishopAttacks | rookAttacks) & board_get_queens(board, color);
}

static void generate_white_pawn_moves(Board board, AttackTable table)
{
    struct BitboardIterator pawn;

    for (bitboard_begin(&pawn, board->pieces[PIECE_WHITE_PAWN]);
        pawn.value;
        bitboard_next(&pawn))
    {
        int target = pawn.current - FILES;

        if (target >= 0 && !(board->squares & bitboard(target)))
        {
            if (pawn.current >= SQUARE_A7 && pawn.current <= SQUARE_H7)
            {
                printf("%s%s=Q\n",
                    square_to_string(pawn.current),
                    square_to_string(target));
                printf("%s%s=R\n",
                    square_to_string(pawn.current),
                    square_to_string(target));
                printf("%s%s=B\n",
                    square_to_string(pawn.current),
                    square_to_string(target));
                printf("%s%s=N\n",
                    square_to_string(pawn.current),
                    square_to_string(target));
            }
            else
            {
                printf("%s%s\n",
                    square_to_string(pawn.current),
                    square_to_string(target));

                if (pawn.current >= SQUARE_A2 && pawn.current <= SQUARE_H2 &&
                    !(board->squares & bitboard(target - FILES)))
                {
                    printf("%s%s\n",
                        square_to_string(pawn.current),
                        square_to_string(target - FILES));
                }
            }
        }

        struct BitboardIterator attack;
        uint64_t attacks = table->pawns[COLOR_WHITE][pawn.current];

        for (bitboard_begin(&attack, attacks& board->colors[COLOR_BLACK]);
            attack.value;
            bitboard_next(&attack))
        {
            if (pawn.current >= SQUARE_A7 && pawn.current <= SQUARE_H7)
            {
                printf("%sx%s=Q\n",
                    square_to_string(pawn.current),
                    square_to_string(attack.current));
                printf("%sx%s=R\n",
                    square_to_string(pawn.current),
                    square_to_string(attack.current));
                printf("%sx%s=B\n",
                    square_to_string(pawn.current),
                    square_to_string(attack.current));
                printf("%sx%s=N\n",
                    square_to_string(pawn.current),
                    square_to_string(attack.current));
            }
            else
            {
                printf("%sx%s\n",
                    square_to_string(pawn.current),
                    square_to_string(attack.current));
            }
        }

        if (board->enPassant != SQUARES)
        {
            uint64_t enPassantAttack = attacks & bitboard(board->enPassant);

            if (enPassantAttack)
            {
                target = bitboard_first(enPassantAttack);

                printf("%sx%s e.p.\n",
                    square_to_string(pawn.current),
                    square_to_string(target));
            }
        }
    }
}

static void generate_black_pawn_moves(Board board, AttackTable table)
{
    struct BitboardIterator pawn;

    for (bitboard_begin(&pawn, board->pieces[PIECE_BLACK_PAWN]);
        pawn.value;
        bitboard_next(&pawn))
    {
        Square target = pawn.current + FILES;

        if (target < SQUARES && !(board->squares & bitboard(target)))
        {
            if (pawn.current >= SQUARE_A2 && pawn.current <= SQUARE_H2)
            {
                printf("%s%s=Q\n",
                    square_to_string(pawn.current),
                    square_to_string(target));
                printf("%s%s=R\n",
                    square_to_string(pawn.current),
                    square_to_string(target));
                printf("%s%s=B\n",
                    square_to_string(pawn.current),
                    square_to_string(target));
                printf("%s%s=N\n",
                    square_to_string(pawn.current),
                    square_to_string(target));
            }
            else
            {
                printf("%s%s\n",
                    square_to_string(pawn.current),
                    square_to_string(target));

                if (pawn.current >= SQUARE_A7 && pawn.current <= SQUARE_H7 &&
                    !(board->squares & bitboard(target + FILES)))
                {
                    printf("%s%s\n",
                        square_to_string(pawn.current),
                        square_to_string(target + FILES));
                }
            }
        }

        struct BitboardIterator attack;
        uint64_t attacks = table->pawns[COLOR_BLACK][pawn.current];

        for (bitboard_begin(&attack, attacks& board->colors[COLOR_WHITE]);
            attack.value;
            bitboard_next(&attack))
        {
            if (pawn.current >= SQUARE_A2 && pawn.current <= SQUARE_H2)
            {
                printf("%sx%s=Q\n",
                    square_to_string(pawn.current),
                    square_to_string(attack.current));
                printf("%sx%s=R\n",
                    square_to_string(pawn.current),
                    square_to_string(attack.current));
                printf("%sx%s=B\n",
                    square_to_string(pawn.current),
                    square_to_string(attack.current));
                printf("%sx%s=N\n",
                    square_to_string(pawn.current),
                    square_to_string(attack.current));
            }
            else
            {
                printf("%sx%s\n",
                    square_to_string(pawn.current),
                    square_to_string(attack.current));
            }
        }

        if (board->enPassant != SQUARES)
        {
            uint64_t enPassantAttack = attacks & bitboard(board->enPassant);

            if (enPassantAttack)
            {
                target = bitboard_first(enPassantAttack);

                printf("%sx%s e.p.\n",
                    square_to_string(pawn.current),
                    square_to_string(target));
            }
        }
    }
}

static void generate_moves(Board board, AttackTable table)
{
    switch (board->color)
    {
    case COLOR_WHITE:
        generate_white_pawn_moves(board, table);
        break;
    case COLOR_BLACK:
        generate_black_pawn_moves(board, table);
        break;
    }

    for (Piece piece = 0; piece < PIECES; piece++)
    {
        uint64_t copy = board->pieces[piece];

    }
}

int main(void)
{
    AttackTable a = malloc(sizeof * a);

    attack_table(a);

    struct Board b;

    board_from_fen_string(
        &b,
        "r3k2r/p11pqpb1/bn2pnp1/2pPN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq c6 0 1");
    board_write_string(stdout, &b, ENCODING_UNICODE);
    generate_moves(&b, a);

    return 0;
}
