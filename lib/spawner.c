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

static void spawner_move(
    List results,
    Square source,
    Square target,
    Piece piece,
    MoveTypes type)
{
    struct Move result =
    {
        .source = source,
        .target = target,
        .piece = piece,
        .type = type
    };

    euler_ok(list_add(results, &result));
}

static void spawner_promotion(
    List results,
    Square source,
    Square target,
    Piece piece,
    MoveTypes promotionType)
{
    spawner_move(
        results, 
        source, 
        target, 
        piece,
        MOVE_TYPES_PROMOTION_KNIGHT | promotionType);
    spawner_move(
        results, 
        source, 
        target, 
        piece,
        MOVE_TYPES_PROMOTION_BISHOP | promotionType);
    spawner_move(
        results, 
        source, 
        target, 
        piece,
        MOVE_TYPES_PROMOTION_ROOK | promotionType);
    spawner_move(
        results, 
        source, 
        target, 
        piece,
        MOVE_TYPES_PROMOTION_QUEEN | promotionType);
}

static void spawner_pawn(List results, Board board, AttackTable table)
{
    int direction;
    Piece piece;
    Square startSquare;
    Square promotionSquare;

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
                spawner_promotion(
                    results,
                    pawn.current,
                    target,
                    piece,
                    MOVE_TYPES_QUIET);
            }
            else
            {
                spawner_move(
                    results,
                    pawn.current,
                    target,
                    piece,
                    MOVE_TYPES_QUIET);

                if (pawn.current >= startSquare &&
                    pawn.current < startSquare + FILES &&
                    !(board->squares & bitboard(target + direction * FILES)))
                {
                    spawner_move(
                        results,
                        pawn.current,
                        target + direction * FILES,
                        piece,
                        MOVE_TYPES_DOUBLE_PUSH);
                }
            }
        }

        struct BitboardIterator attack;
        uint64_t attacks = table->pawns[board->color][pawn.current];

        for (bitboard_begin(&attack, attacks & board->colors[!board->color]);
             attack.value;
             bitboard_next(&attack))
        {
            if (pawn.current >= promotionSquare &&
                pawn.current < promotionSquare + FILES)
            {
                spawner_promotion(
                    results,
                    pawn.current,
                    attack.current,
                    piece,
                    MOVE_TYPES_CAPTURE);
            }
            else
            {
                spawner_move(
                    results,
                    pawn.current,
                    attack.current,
                    piece,
                    MOVE_TYPES_CAPTURE);
            }
        }

        if (board->enPassant != SQUARES)
        {
            uint64_t enPassantAttack = attacks & bitboard(board->enPassant);

            if (enPassantAttack)
            {
                spawner_move(
                    results,
                    pawn.current,
                    bitboard_first(enPassantAttack),
                    piece,
                    MOVE_TYPES_EN_PASSANT_CAPTURE);
            }
        }
    }
}

static void spawner_castle(List results, Board board, AttackTable table)
{
    Piece piece;
    Square square;
    CastlingRights kingside;
    CastlingRights queenside;

    if (board->color)
    {
        square = SQUARE_A8;
        kingside = CASTLING_RIGHTS_BLACK_KINGSIDE;
        queenside = CASTLING_RIGHTS_BLACK_QUEENSIDE;
        piece = PIECE_BLACK_KING;
    }
    else
    {
        square = SQUARE_A1;
        kingside = CASTLING_RIGHTS_WHITE_KINGSIDE;
        queenside = CASTLING_RIGHTS_WHITE_QUEENSIDE;
        piece = PIECE_WHITE_KING;
    }

    if (board->castlingRights & kingside)
    {
        if (!(board->squares & bitboard(square + FILE_F)) &&
            !(board->squares & bitboard(square + FILE_G)) &&
            !is_square_attacked(board, table, square + FILE_E, !board->color) &&
            !is_square_attacked(board, table, square + FILE_F, !board->color))
        {
            spawner_move(
                results,
                square + FILE_E,
                square + FILE_G,
                piece,
                MOVE_TYPES_CASTLE_KINGSIDE);
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
            spawner_move(
                results,
                square + FILE_E,
                square + FILE_C,
                piece,
                MOVE_TYPES_CASTLE_QUEENSIDE);
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
    if (board->color)
    {
        piece = piece + PIECE_BLACK_PAWN;
    }

    struct BitboardIterator item;

    for (bitboard_begin(&item, board->pieces[piece]);
         item.value;
         bitboard_next(&item))
    {
        uint64_t attacks = factory(table, item.current, board->squares);
        struct BitboardIterator attack;

        for (bitboard_begin(&attack, attacks & ~board->colors[board->color]);
             attack.value;
             bitboard_next(&attack))
        {
            MoveTypes type;

            if (board->colors[!board->color] & bitboard(attack.current))
            {
                type = MOVE_TYPES_CAPTURE;
            }
            else
            {
                type = MOVE_TYPES_QUIET;
            }

            spawner_move(results, item.current, attack.current, piece, type);
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
