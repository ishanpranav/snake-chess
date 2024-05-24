// zobrist.h
// Licensed under the MIT license.

#ifndef ZOBRIST_b47d07bdd59c484c966e0966db49390f
#define ZOBRIST_b47d07bdd59c484c966e0966db49390f
#include <stdint.h>
#include "castling_rights.h"
#include "piece.h"
#include "square.h"
#define ZOBRIST_SEED 1804289383

/** */
struct Zobrist
{
    uint64_t pieces[PIECES][SQUARES];
    uint64_t color;
    uint64_t enPassant[SQUARES];
    uint64_t castlingRights[CASTLING_RIGHTS];
};

/** */
typedef struct Zobrist* Zobrist;

/**
 * 
 * @param instance
 * @param state
*/
void zobrist(Zobrist instance, uint32_t* state);

#endif
