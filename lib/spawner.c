// spawner.c
// Licensed under the MIT license.

#include "attack_provider.h"
#include "bitboard_iterator.h"
#include "file.h"
#include "move.h"
#include "spawner.h"

static bool is_square_attacked(
    Board board,
    AttackTable attacks,
    Square square,
    Color color)
{
    if ((attacks->kings[square] & board_get(board, color, PIECE_KING)) ||
        (attacks->knights[square] & board_get(board, color, PIECE_KNIGHT)) ||
        (attacks->pawns[!color][square] & board_get(board, color, PIECE_PAWN)))
    {
        return true;
    }

    uint64_t bishopAttacks = bishop_attack_provider(
        attacks,
        square,
        board->squares);

    if (bishopAttacks & board_get(board, color, PIECE_BISHOP))
    {
        return true;
    }

    uint64_t rookAttacks = rook_attack_provider(
        attacks,
        square,
        board->squares);

    if (rookAttacks & board_get(board, color, PIECE_ROOK))
    {
        return true;
    }

    return (bishopAttacks | rookAttacks) & board_get(board, color, PIECE_QUEEN);
}

static void spawner_promotion(List results, Move move)
{
    Piece promotion = move->promotion;

    euler_ok(list_ensure_capacity(results, 4));

    move->promotion = PIECE_QUEEN;

    list_add(results, move);

    move->promotion = PIECE_ROOK;

    list_add(results, move);

    move->promotion = PIECE_BISHOP;

    list_add(results, move);

    move->promotion = PIECE_KNIGHT;

    list_add(results, move);

    move->promotion = promotion;
}

static void spawner_pawn(List results, Board board, AttackTable table)
{
    int direction;
    Piece coloredPiece;
    Square startSquare;
    Square promotionSquare;
    struct Move result =
    {
        .piece = PIECE_PAWN,
        .promotion = PIECES
    };

    if (board->color)
    {
        direction = 1;
        startSquare = SQUARE_A7;
        promotionSquare = SQUARE_A2;
        coloredPiece = PIECE_BLACK_PAWN;
    }
    else
    {
        direction = -1;
        startSquare = SQUARE_A2;
        promotionSquare = SQUARE_A7;
        coloredPiece = PIECE_WHITE_PAWN;
    }

    struct BitboardIterator pawn;

    for (bitboard_begin(&pawn, board->pieces[coloredPiece]);
        pawn.value;
        bitboard_next(&pawn))
    {
        int target = pawn.current + direction * FILES;

        result.source = pawn.current;
        result.target = target;
        result.type = MOVE_TYPE_QUIET;

        if (target < SQUARES && !(board->squares & bitboard(target)))
        {
            if (pawn.current >= promotionSquare &&
                pawn.current < promotionSquare + FILES)
            {
                spawner_promotion(results, &result);
            }
            else
            {
                euler_ok(list_add(results, &result));

                if (pawn.current >= startSquare &&
                    pawn.current < startSquare + FILES &&
                    !(board->squares & bitboard(target + direction * FILES)))
                {
                    result.type = MOVE_TYPE_DOUBLE_PUSH;

                    euler_ok(list_add(results, &result));

                    result.type = MOVE_TYPE_QUIET;
                }
            }
        }

        struct BitboardIterator attack;
        uint64_t attacks = table->pawns[board->color][pawn.current];

        result.type = MOVE_TYPE_CAPTURE;

        for (bitboard_begin(&attack, attacks& board->colors[!board->color]);
            attack.value;
            bitboard_next(&attack))
        {
            if (pawn.current >= promotionSquare &&
                pawn.current < promotionSquare + FILES)
            {
                spawner_promotion(results, &result);
            }
            else
            {
                euler_ok(list_add(results, &result));
            }
        }

        if (board->enPassant != SQUARES)
        {
            uint64_t enPassantAttack = attacks & bitboard(board->enPassant);

            if (enPassantAttack)
            {
                target = bitboard_first(enPassantAttack);

                result.type = MOVE_TYPE_EN_PASSANT;

                euler_ok(list_add(results, &result));

                result.type = MOVE_TYPE_QUIET;
            }
        }
    }
}

static void spawner_castle(List results, Board board, AttackTable table)
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

    struct Move result =
    {
        .piece = PIECE_KING,
        .promotion = PIECES
    };

    if (board->castlingRights & kingside)
    {
        if (!(board->squares & bitboard(square + FILE_F)) &&
            !(board->squares & bitboard(square + FILE_G)) &&
            !is_square_attacked(board, table, square + FILE_E, !board->color) &&
            !is_square_attacked(board, table, square + FILE_F, !board->color))
        {
            result.source = square + FILE_E;
            result.target = square + FILE_G;
            result.type = MOVE_TYPE_CASTLE_KINGSIDE;

            euler_ok(list_add(results, &result));
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
            result.source = square + FILE_E;
            result.target = square + FILE_C;
            result.type = MOVE_TYPE_CASTLE_QUEENSIDE;

            euler_ok(list_add(results, &result));
        }
    }
}

static void spawner_piece(
    List results,
    Board board,
    AttackTable table,
    AttackProvider factory,
    Piece piece)
{
    Piece coloredPiece;

    if (board->color)
    {
        coloredPiece = piece + PIECE_BLACK_PAWN;
    }
    else
    {
        coloredPiece = piece;
    }

    struct BitboardIterator item;

    for (bitboard_begin(&item, board->pieces[coloredPiece]);
        item.value;
        bitboard_next(&item))
    {
        uint64_t attacks = factory(table, item.current, board->squares);
        struct BitboardIterator attack;

        for (bitboard_begin(&attack, attacks & ~board->colors[board->color]);
            attack.value;
            bitboard_next(&attack))
        {
            struct Move result =
            {
                .source = item.current,
                .target = attack.current,
                .piece = piece,
                .promotion = PIECES
            };

            if (board->colors[!board->color] & bitboard(attack.current))
            {
                result.type = MOVE_TYPE_CAPTURE;
            }
            else
            {
                result.type = MOVE_TYPE_QUIET;
            }

            euler_ok(list_add(results, &result));
        }
    }
}

void spawner_generate_moves(List results, Board board, AttackTable table)
{
    spawner_pawn(results, board, table);
    spawner_castle(results, board, table);
    spawner_piece(results, board, table, knight_attack_provider, PIECE_KNIGHT);
    spawner_piece(results, board, table, bishop_attack_provider, PIECE_BISHOP);
    spawner_piece(results, board, table, rook_attack_provider, PIECE_ROOK);
    spawner_piece(results, board, table, queen_attack_provider, PIECE_QUEEN);
    spawner_piece(results, board, table, king_attack_provider, PIECE_KING);
}
