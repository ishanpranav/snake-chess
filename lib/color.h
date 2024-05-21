// color.h
// Licensed under the MIT license.

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
Color color_from_fen_char(char value);

/**
 *
 * @param value
 * @return
*/
String color_to_string(Color value);
