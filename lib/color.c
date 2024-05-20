// color.c
// Licensed under the MIT license.

#include "color.h"

static String COLOR_STRINGS[] = { "white", "black" };

String color_to_string(Color value)
{
    return COLOR_STRINGS[value];
}
