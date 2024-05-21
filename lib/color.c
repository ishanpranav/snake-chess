// color.c
// Licensed under the MIT license.

#include "color.h"

static String COLOR_STRINGS[] = { "white", "black", "none" };

Color color_from_fen_char(char value)
{
    switch (value)
    {
    case 'b': return COLOR_BLACK;
    case 'w': return COLOR_WHITE;
    default: return COLORS;
    }
}

String color_to_string(Color value)
{
    return COLOR_STRINGS[value];
}
