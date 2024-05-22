// move_type.h
// Licensed under the MIT license.

/** */
enum MoveType
{
    MOVE_TYPE_QUIET,
    MOVE_TYPE_CAPTURE,
    MOVE_TYPE_DOUBLE_PUSH,
    MOVE_TYPE_EN_PASSANT,
    MOVE_TYPE_CASTLE_KINGSIDE,
    MOVE_TYPE_CASTLE_QUEENSIDE
};

/** */
typedef enum MoveType MoveType;
