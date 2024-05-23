// string.c
// Copyright (c) 2024 Ishan Pranav
// Licensed under the MIT license.

// Retrieved from https://github.com/ishanpranav/codebook

// https://github.com/ishanpranav/codebook/blob/master/lib/string.c

#include <string.h>
#include "euler.h"

bool string_starts_with(String instance, String value)
{
    return strncmp(instance, value, strlen(value)) == 0;
}
