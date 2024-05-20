// color.h
// Licensed under the MIT license.

#ifndef COLOR_c4598acdc65d4a60b9ef829a6c11d757
#define COLOR_c4598acdc65d4a60b9ef829a6c11d757
#include "../ishan/euler.h"

/** */
enum Color
{
    COLOR_WHITE,
    COLOR_BLACK,
    COLORS
};

/** */
typedef enum Color Color;

/**
 *
 * @param value
 * @return
*/
String color_to_string(Color value);

#endif
