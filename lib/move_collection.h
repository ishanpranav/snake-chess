// move_collection.h
// Licensed under the MIT license.

#include "move.h"

/** */
struct MoveCollection
{
    int count;
    struct Move items[256];
};

/** */
typedef struct MoveCollection* MoveCollection;

/**
 * 
 * @param instance
*/
void move_collection(MoveCollection instance);
