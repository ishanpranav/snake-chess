// move.c
// Licensed under the MIT license.

#include <string.h>
#include "bitboard.h"
#include "check.h"
#include "file.h"
#include "spawn.h"
#define move_insert(board, piece, target, zobrist) macro \
(board)->pieces[(piece)] |= bitboard((target)); \
(board)->hash ^= (zobrist)->pieces[(piece)][(target)]; \
end_macro
#define move_remove(board, piece, source, zobrist) macro \
(board)->pieces[(piece)] &= ~bitboard((source));\
(board)->hash ^= (zobrist)->pieces[(piece)][(source)];\
end_macro

void move_from_null(Move result)
{
    result->piece = PIECES;
    result->source = SQUARES;
    result->target = SQUARES;
    result->type = MOVE_TYPES_QUIET;
}

bool move_from_uci_string(
    Move result,
    String value,
    Board board,
    AttackTable table)
{
    struct MoveCollection moves;

    move_collection(&moves);
    spawn(&moves, board, table);

    for (int i = 0; i < moves.count; i++)
    {
        char buffer[8] = { 0 };

        move_write_uci_string(buffer, moves.items + i);

        if (strcmp(buffer, value) == 0)
        {
            *result = moves.items[i];

            return true;
        }
    }

    return false;
}

Piece move_get_capture(Move instance, Board board, Piece enemyOffset)
{
    if (instance->type & MOVE_TYPES_EN_PASSANT)
    {
        return enemyOffset + PIECE_PAWN;
    }

    if (instance->type & MOVE_TYPES_CAPTURE)
    {
        Piece enemyKing = enemyOffset + PIECE_KING;

        for (Piece piece = enemyOffset; piece <= enemyKing; piece++)
        {
            if (board->pieces[piece] & bitboard(instance->target))
            {
                return piece;
            }
        }
    }

    return PIECES;
}

void move_apply(Move instance, Board board, Zobrist zobrist)
{
    Square source = instance->source;
    Square target = instance->target;

    move_remove(board, instance->piece, source, zobrist);
    move_insert(board, instance->piece, target, zobrist);

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
        Piece capture = move_get_capture(instance, board, enemyBegin);

        move_remove(board, capture, target, zobrist);
    }

    if (board->enPassant != SQUARES)
    {
        board->hash ^= zobrist->enPassant[board->enPassant];
        board->enPassant = SQUARES;
    }

    if (instance->type & MOVE_TYPES_PROMOTION)
    {
        move_remove(board, friendBegin + PIECE_PAWN, target, zobrist);

        if (instance->type & MOVE_TYPES_KNIGHT)
        {
            move_insert(board, friendBegin + PIECE_KNIGHT, target, zobrist);
        }
        else if (instance->type & MOVE_TYPES_BISHOP)
        {
            move_insert(board, friendBegin + PIECE_BISHOP, target, zobrist);
        }
        else if (instance->type & MOVE_TYPES_ROOK)
        {
            move_insert(board, friendBegin + PIECE_ROOK, target, zobrist);
        }
        else
        {
            move_insert(board, friendBegin + PIECE_QUEEN, target, zobrist);
        }
    }
    else if (instance->type & MOVE_TYPES_EN_PASSANT)
    {
        move_remove(
            board,
            enemyBegin + PIECE_PAWN,
            target + direction * FILES,
            zobrist);
    }
    else if (instance->type & MOVE_TYPES_DOUBLE_PUSH)
    {
        Square enPassantTarget = target + direction * FILES;

        board->enPassant = enPassantTarget;
        board->hash ^= zobrist->enPassant[enPassantTarget];
    }
    else if (instance->type & MOVE_TYPES_KINGSIDE)
    {
        move_remove(board, friendBegin + PIECE_ROOK, source + 3, zobrist);
        move_insert(board, friendBegin + PIECE_ROOK, source + 1, zobrist);
    }
    else if (instance->type & MOVE_TYPES_QUEENSIDE)
    {
        move_remove(board, friendBegin + PIECE_ROOK, source - 4, zobrist);
        move_insert(board, friendBegin + PIECE_ROOK, source - 1, zobrist);
    }

    CastlingRights castlingRights = board->castlingRights;

    board->hash ^= zobrist->castlingRights[castlingRights];
    castlingRights = castling_rights_remove(castlingRights, source);
    castlingRights = castling_rights_remove(castlingRights, target);
    board->hash ^= zobrist->castlingRights[castlingRights];
    board->castlingRights = castlingRights;
    board->color = !board->color;
    board->hash ^= zobrist->color;

    board_save_changes(board);
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

void move_write_uci_string(char buffer[], Move instance)
{
    String promotion;

    if (instance->type & MOVE_TYPES_KNIGHT)
    {
        promotion = "n";
    }
    else if (instance->type & MOVE_TYPES_BISHOP)
    {
        promotion = "b";
    }
    else if (instance->type & MOVE_TYPES_ROOK)
    {
        promotion = "r";
    }
    else if (instance->type & MOVE_TYPES_QUEEN)
    {
        promotion = "q";
    }
    else
    {
        promotion = "";
    }

    sprintf(buffer, "%s%s%s",
        square_to_string(instance->source),
        square_to_string(instance->target),
        promotion);
}
