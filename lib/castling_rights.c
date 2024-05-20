// castling_rights.c
// Licensed under the MIT license.

#include "castling_rights.h"

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
