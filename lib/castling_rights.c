// castling_rights.c
// Licensed under the MIT license.

#include "castling_rights.h"

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
