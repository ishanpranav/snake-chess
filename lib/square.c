// square.c
// Licensed under the MIT license.

#include <ctype.h>
#include "file.h"
#include "square.h"

static String SQUARE_STRINGS[] =
{
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
    "00"
};

Square square_from_fen_string(String value)
{
    if (!isalpha(value[0]) || !isdigit(value[1]))
    {
        return SQUARES;
    }

    return (8 - (value[1] - '0')) * FILES + value[0] - 'a';
}

String square_to_string(Square value)
{
    return SQUARE_STRINGS[value];
}
