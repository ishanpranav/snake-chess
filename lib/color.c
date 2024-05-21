// color.c
// Licensed under the MIT license.

#include "color.h"

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
    switch (value)
    {
    case COLOR_WHITE: return "white";
    case COLOR_BLACK: return "black";
    default: return "none";
    }
}
