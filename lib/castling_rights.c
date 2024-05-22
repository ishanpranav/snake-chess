// castling_rights.c
// Licensed under the MIT license.

#include <stdint.h>
#include "castling_rights.h"

static int castling_rights_get_status(Square square)
{
    switch (square)
    {
    case SQUARE_A1: return 0xd;
    case SQUARE_E1: return 0xc;
    case SQUARE_H1: return 0xe;
    case SQUARE_A8: return 0x7;
    case SQUARE_E8: return 0x3;
    case SQUARE_H8: return 0xb;
    default: return 0xf;
    }
}

CastlingRights castling_rights_remove(CastlingRights value, Square square)
{
    return value & castling_rights_get_status(square);
}

CastlingRights castling_rights_from_fen_string(String value)
{
    CastlingRights result = CASTLING_RIGHTS_NONE;

    for (; *value; value++)
    {
        switch (*value)
        {
        case 'K':
            result |= CASTLING_RIGHTS_WHITE_KINGSIDE;
            break;

        case 'Q':
            result |= CASTLING_RIGHTS_WHITE_QUEENSIDE;
            break;

        case 'k':
            result |= CASTLING_RIGHTS_BLACK_KINGSIDE;
            break;

        case 'q':
            result |= CASTLING_RIGHTS_BLACK_QUEENSIDE;
            break;

        default: return result;
        }
    }

    return result;
}

void castling_rights_write_string(Stream output, CastlingRights value)
{
    fprintf(
        output,
        "%c%c%c%c",
        (value & CASTLING_RIGHTS_WHITE_KINGSIDE) ? 'K' : '-',
        (value & CASTLING_RIGHTS_WHITE_QUEENSIDE) ? 'Q' : '-',
        (value & CASTLING_RIGHTS_BLACK_KINGSIDE) ? 'k' : '-',
        (value & CASTLING_RIGHTS_BLACK_QUEENSIDE) ? 'q' : '-');
}
