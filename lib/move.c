// move.c
// Licensed under the MIT license.

#include "bitboard.h"
#include "check.h"
#include "move.h"
#include "file.h"

static void move_put(Board board, Piece piece, uint64_t source, uint64_t target)
{
    board->pieces[piece] &= ~source;
    board->pieces[piece] |= target;
}

bool move_try(Move instance, Board board, AttackTable table)
{
    struct Board clone = *board;
    uint64_t source = bitboard(instance->source);
    uint64_t target = bitboard(instance->target);

    move_put(board, instance->piece, source, target);

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

    if (instance->type & MOVE_TYPES_CAPTURE)
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

    if (instance->type & MOVE_TYPES_PROMOTION)
    {
        board->pieces[friendBegin + PIECE_PAWN] &= ~target;

        if (instance->type & MOVE_TYPES_KNIGHT)
        {
            board->pieces[friendBegin + PIECE_KNIGHT] |= target;
        }
        else if (instance->type & MOVE_TYPES_BISHOP)
        {
            board->pieces[friendBegin + PIECE_BISHOP] |= target;
        }
        else if (instance->type & MOVE_TYPES_ROOK)
        {
            board->pieces[friendBegin + PIECE_ROOK] |= target;
        }
        else if (instance->type & MOVE_TYPES_QUEEN)
        {
            board->pieces[friendBegin + PIECE_QUEEN] |= target;
        }
    }

    if (instance->type & MOVE_TYPES_EN_PASSANT)
    {
        Square enPassantTarget = instance->target + direction * FILES;

        board->pieces[enemyBegin + PIECE_PAWN] &= ~bitboard(enPassantTarget);
    }

    board->enPassant = SQUARES;

    if (instance->type & MOVE_TYPES_DOUBLE_PUSH)
    {
        board->enPassant = instance->target + direction * FILES;
    }

    if (instance->type & MOVE_TYPES_KINGSIDE)
    {
        move_put(
            board,
            friendBegin + PIECE_ROOK,
            bitboard(instance->source + 3),
            bitboard(instance->source + 1));
    }

    if (instance->type & MOVE_TYPES_QUEENSIDE)
    {
        move_put(
            board,
            friendBegin + PIECE_ROOK,
            bitboard(instance->source - 4),
            bitboard(instance->source - 1));
    }

    CastlingRights castlingRights = board->castlingRights;

    castlingRights = castling_rights_remove(castlingRights, instance->source);
    castlingRights = castling_rights_remove(castlingRights, instance->target);
    board->castlingRights = castlingRights;

    board_save_changes(board);

    Square kingSquare = bitboard_first(board->pieces[friendBegin + PIECE_KING]);

    if (check_test(board, table, kingSquare, !board->color))
    {
        *board = clone;

        return false;
    }

    board->color = !board->color;

    return true;
}

void move_write_string(Stream output, Move instance)
{
    if (instance->type & MOVE_TYPES_KINGSIDE)
    {
        fprintf(output, "O-O");
    }

    if (instance->type & MOVE_TYPES_QUEENSIDE)
    {
        fprintf(output, "O-O-O");
    }

    if (instance->type & MOVE_TYPES_CASTLE)
    {
        return;
    }

    fprintf(output, "%s", piece_to_string(instance->piece, ENCODING_ALGEBRAIC));

    if (instance->piece != PIECE_WHITE_KING &&
        instance->piece != PIECE_BLACK_KING)
    {
        fprintf(output, "%s", square_to_string(instance->source));
    }

    if (instance->type & MOVE_TYPES_CAPTURE)
    {
        fprintf(output, "x");
    }

    fprintf(output, "%s", square_to_string(instance->target));

    if (instance->type & MOVE_TYPES_PROMOTION)
    {
        fprintf(output, "=");
    }

    if (instance->type & MOVE_TYPES_KNIGHT)
    {
        fprintf(output, "N");
    }
    else if (instance->type & MOVE_TYPES_BISHOP)
    {
        fprintf(output, "B");
    }
    else if (instance->type & MOVE_TYPES_ROOK)
    {
        fprintf(output, "R");
    }
    else if (instance->type & MOVE_TYPES_QUEEN)
    {
        fprintf(output, "Q");
    }

    if (instance->type & MOVE_TYPES_EN_PASSANT)
    {
        fprintf(output, " e.p.");
    }
}

void move_write_uci_string(Stream output, Move instance)
{
    fprintf(
        output,
        "%s%s",
        square_to_string(instance->source),
        square_to_string(instance->target));

    if (instance->type & MOVE_TYPES_PROMOTION_KNIGHT)
    {
        fprintf(output, "n");
    }
    else  if (instance->type & MOVE_TYPES_PROMOTION_BISHOP)
    {
        fprintf(output, "b");
    }
    else if (instance->type & MOVE_TYPES_PROMOTION_ROOK)
    {
        fprintf(output, "r");
    }
    else if (instance->type & MOVE_TYPES_PROMOTION_QUEEN)
    {
        fprintf(output, "q");
    }
}
