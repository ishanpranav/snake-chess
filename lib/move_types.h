// move_types.h
// Licensed under the MIT license.

/** */
enum MoveTypes
{
    MOVE_TYPES_QUIET = 0,
    MOVE_TYPES_CAPTURE = 1 << 0,
    MOVE_TYPES_PROMOTION = 1 << 1,
    MOVE_TYPES_KNIGHT = 1 << 2,
    MOVE_TYPES_PROMOTION_KNIGHT = MOVE_TYPES_PROMOTION | MOVE_TYPES_KNIGHT,

    MOVE_TYPES_PROMOTION_KNIGHT_CAPTURE =
    MOVE_TYPES_CAPTURE | MOVE_TYPES_PROMOTION_KNIGHT,

    MOVE_TYPES_BISHOP = 1 << 3,
    MOVE_TYPES_PROMOTION_BISHOP = MOVE_TYPES_PROMOTION | MOVE_TYPES_BISHOP,

    MOVE_TYPES_PROMOTION_BISHOP_CAPTURE =
    MOVE_TYPES_CAPTURE | MOVE_TYPES_PROMOTION_BISHOP,

    MOVE_TYPES_ROOK = 1 << 4,
    MOVE_TYPES_PROMOTION_ROOK = MOVE_TYPES_PROMOTION | MOVE_TYPES_ROOK,

    MOVE_TYPES_PROMOTION_ROOK_CAPTURE =
    MOVE_TYPES_CAPTURE | MOVE_TYPES_PROMOTION_ROOK,

    MOVE_TYPES_QUEEN = 1 << 5,
    MOVE_TYPES_PROMOTION_QUEEN = MOVE_TYPES_PROMOTION | MOVE_TYPES_QUEEN,

    MOVE_TYPES_PROMOTION_QUEEN_CAPTURE =
    MOVE_TYPES_CAPTURE | MOVE_TYPES_PROMOTION_QUEEN,

    MOVE_TYPES_EN_PASSANT = 1 << 6,
    MOVE_TYPES_EN_PASSANT_CAPTURE = MOVE_TYPES_CAPTURE | MOVE_TYPES_EN_PASSANT,
    MOVE_TYPES_DOUBLE_PUSH = 1 << 7,
    MOVE_TYPES_CASTLE = 1 << 8,
    MOVE_TYPES_KINGSIDE = 1 << 9,
    MOVE_TYPES_CASTLE_KINGSIDE = MOVE_TYPES_CASTLE | MOVE_TYPES_KINGSIDE,
    MOVE_TYPES_QUEENSIDE = 1 << 10,
    MOVE_TYPES_CASTLE_QUEENSIDE = MOVE_TYPES_CASTLE | MOVE_TYPES_QUEENSIDE
};

/** */
typedef enum MoveTypes MoveTypes;
