// search.c
// Licensed under the MIT license.

#include "../search.h"
#include "../spawn.h"

void search(Move result, Board board, AttackTable table, EULER_UNUSED int depth)
{
    struct MoveCollection moves;

    move_collection(&moves);
    spawn(&moves, board, table);

    for (int i = 0; i < moves.count; i++)
    {
        if (move_is_legal(moves.items + i, board, table))
        {
            *result = moves.items[i];

            return;
        }
    }

    move_from_null(result);
}