// square.c
// Licensed under the MIT license.

#include "square.h"

static const char* SQUARE_STRINGS[] =
{
    #include "../data/square-strings.csv"
};

const char* square_to_string(Square value)
{
    return SQUARE_STRINGS[value];
}
