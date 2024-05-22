// check.c
// Licensed under the MIT license.

#include "attack_provider.h"
#include "bitboard.h"
#include "check.h"

bool check_test(Board board, AttackTable table, Square square, Color color)
{
    Piece offset = 0;

    if (color)
    {
        offset += PIECE_BLACK_PAWN;
    }

    if ((table->kings[square] & board->pieces[offset + PIECE_KING]) ||
        (table->knights[square] & board->pieces[offset + PIECE_KNIGHT]) ||
        (table->pawns[!color][square] & board->pieces[offset + PIECE_PAWN]))
    {
        return true;
    }

    uint64_t bishopAttacks = bishop_attack_provider(
        table,
        square,
        board->squares);

    if (bishopAttacks & board->pieces[offset + PIECE_BISHOP])
    {
        return true;
    }

    uint64_t rookAttacks = rook_attack_provider(
        table,
        square,
        board->squares);

    if (rookAttacks & board->pieces[offset + PIECE_ROOK])
    {
        return true;
    }

    return (bishopAttacks | rookAttacks) & board->pieces[offset + PIECE_QUEEN];
}

bool check_test_position(Board board, AttackTable table)
{
    Piece king = PIECE_KING;

    if (!board->color)
    {
        king += PIECE_BLACK_PAWN;
    }

    Square kingSquare = bitboard_first(board->pieces[king]);

    return check_test(board, table, kingSquare, board->color);
}
