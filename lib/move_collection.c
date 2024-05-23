// move_collection.c
// Licensed under the MIT license.

#include "move_collection.h"

void move_collection(MoveCollection instance)
{
    instance->count = 0;
}

void move_collection_add(MoveCollection instance, Move item)
{
    instance->items[instance->count] = *item;
    instance->count++;
}
