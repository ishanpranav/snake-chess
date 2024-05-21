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

static void generate_pawn_moves(Board board, AttackTable table)
{
    int direction;
    Square startSquare;
    Square promotionSquare;
    Piece piece;

    if (board->color)
    {
        direction = 1;
        startSquare = SQUARE_A7;
        promotionSquare = SQUARE_A2;
        piece = PIECE_BLACK_PAWN;
    }
    else
    {
        direction = -1;
        startSquare = SQUARE_A2;
        promotionSquare = SQUARE_A7;
        piece = PIECE_WHITE_PAWN;
    }

    struct BitboardIterator pawn;

    for (bitboard_begin(&pawn, board->pieces[piece]);
        pawn.value;
        bitboard_next(&pawn))
    {
        int target = pawn.current + direction * FILES;

        if (target < SQUARES && !(board->squares & bitboard(target)))
        {
            if (pawn.current >= promotionSquare &&
                pawn.current < promotionSquare + FILES)
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

                if (pawn.current >= startSquare &&
                    pawn.current < startSquare + FILES &&
                    !(board->squares & bitboard(target + direction * FILES)))
                {
                    printf("%s%s\n",
                        square_to_string(pawn.current),
                        square_to_string(target + direction * FILES));
                }
            }
        }

        struct BitboardIterator attack;
        uint64_t attacks = table->pawns[board->color][pawn.current];

        for (bitboard_begin(&attack, attacks& board->colors[!board->color]);
            attack.value;
            bitboard_next(&attack))
        {
            if (pawn.current >= promotionSquare &&
                pawn.current < promotionSquare + FILES)
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

static void generate_castle_moves(Board board, AttackTable table)
{
    Square square;
    CastlingRights kingside;
    CastlingRights queenside;

    if (board->color)
    {
        square = SQUARE_A8;
        kingside = CASTLING_RIGHTS_BLACK_KINGSIDE;
        queenside = CASTLING_RIGHTS_BLACK_QUEENSIDE;
    }
    else
    {
        square = SQUARE_A1;
        kingside = CASTLING_RIGHTS_WHITE_KINGSIDE;
        queenside = CASTLING_RIGHTS_WHITE_QUEENSIDE;
    }

    if (board->castlingRights & kingside)
    {
        if (!(board->squares & bitboard(square + FILE_F)) &&
            !(board->squares & bitboard(square + FILE_G)) &&
            !is_square_attacked(board, table, square + FILE_E, !board->color) &&
            !is_square_attacked(board, table, square + FILE_F, !board->color))
        {
            printf("O-O\n");
        }
    }

    if (board->castlingRights & queenside)
    {
        if (!(board->squares & bitboard(square + FILE_B)) &&
            !(board->squares & bitboard(square + FILE_C)) &&
            !(board->squares & bitboard(square + FILE_D)) &&
            !is_square_attacked(board, table, square + FILE_D, !board->color) &&
            !is_square_attacked(board, table, square + FILE_E, !board->color))
        {
            printf("O-O-O\n");
        }
    }
}

static void generate_moves(Board board, AttackTable table)
{
    generate_pawn_moves(board, table);
    generate_castle_moves(board, table);

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
        "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQkq - 0 1");
    board_write_string(stdout, &b, ENCODING_UNICODE);
    generate_moves(&b, a);
    free(a);

    return 0;
}
