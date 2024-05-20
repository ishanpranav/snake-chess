// castling_rights.h
// Licensed under the MIT license.

#include "../ishan/stream.h"

/** */
enum CastlingRights
{
    CASTLING_RIGHTS_NONE = 0,
    CASTLING_RIGHTS_WHITE_KINGSIDE = 1,
    CASTLING_RIGHTS_WHITE_QUEENSIDE = 2,
    CASTLING_RIGHTS_BLACK_KINGSIDE = 4,
    CASTLING_RIGHTS_BLACK_QUEENSIDE = 8
};

/** */
typedef enum CastlingRights CastlingRights;

/**
 *
 * @param output
 * @param value
 * @return
*/
void castling_rights_write_string(Stream output, CastlingRights value);
