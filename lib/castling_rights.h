// castling_rights.h
// Licensed under the MIT license.

#ifndef CASTLING_RIGHTS_e5c418541653448f828dd071d6a1b0da
#define CASTLING_RIGHTS_e5c418541653448f828dd071d6a1b0da
#include "../ishan/euler.h"
#include "../ishan/stream.h"
#include "square.h"

/** */
enum CastlingRights
{
    CASTLING_RIGHTS_NONE = 0,
    CASTLING_RIGHTS_WHITE_KINGSIDE = 1 << 0,
    CASTLING_RIGHTS_WHITE_QUEENSIDE = 1 << 1,
    CASTLING_RIGHTS_BLACK_KINGSIDE = 1 << 2,
    CASTLING_RIGHTS_BLACK_QUEENSIDE = 1 << 3,
    CASTLING_RIGHTS = 1 << 4
};

/** */
typedef enum CastlingRights CastlingRights;

/**
 *
 * @param value
 * @param square
 * @return
*/
CastlingRights castling_rights_remove(CastlingRights value, Square square);

/**
 *
 * @param value
 * @return
*/
CastlingRights castling_rights_from_fen_string(String value);

/**
 *
 * @param output
 * @param value
 * @return
*/
void castling_rights_write_string(Stream output, CastlingRights value);

#endif
