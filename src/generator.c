// generator.c
// Licensed under the MIT license.

#include <stdbool.h>
#include "../lib/attack_table.h"
#include "../lib/bitboard.h"
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

int main(void)
{
    struct AttackTable a;
    struct Board b;

    attack_table(&a);
    board_from_fen_string(&b, BOARD_INITIAL);
    board_write_string(stdout, &b, ENCODING_UNICODE);

    uint64_t bb = 0;

    for (Square s = 0; s < SQUARES; s++) {
        if (is_square_attacked(&b, &a, s, COLOR_BLACK)) {
            bb |= bitboard(s);
        }
    }

    bitboard_write_string(stdout, bb);

    return 0;
}
