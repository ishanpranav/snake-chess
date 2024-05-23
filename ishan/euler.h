// euler.h
// Copyright (c) 2024 Ishan Pranav
// Licensed under the MIT license.

// Retrieved from https://github.com/ishanpranav/codebook

// https://github.com/ishanpranav/codebook/blob/master/lib/euler.h

#ifndef EULER_2363b2bd9868485c9651b89fbe7082ba
#define EULER_2363b2bd9868485c9651b89fbe7082ba
#include <stdbool.h>
#define macro do {
#define end_macro } while (0)
#define euler_assert(condition) macro if (!(condition)) { \
    fprintf(stderr, "Faulted: %s line %d.\n", __FILE__, __LINE__); \
    exit(1); } end_macro
#ifdef __GNUC__
#define EULER_UNUSED __attribute__((unused))
#else
#define EULER_UNUSED
#endif

/** Represents text as a zero-terminated sequence of characters. */
typedef const char* String;

/**
 * Determines whether the beginning of this string instance matches the
 * specified string.
 *
 * @param instance the string instance.
 * @param value    the string to compare.
 * @return `true` if the `value` parameter matches the beginning of this string;
 *         otherwise, `false`.
*/
bool string_starts_with(String instance, String value);

#endif
