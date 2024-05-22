// list.h
// Copyright (c) 2024 Ishan Pranav
// Licensed under the MIT license.

// Retrieved from https://github.com/ishanpranav/codebook

// https://github.com/ishanpranav/codebook/blob/master/lib/list.h

#ifndef LIST_95a94c0379b44bd3967523c81d4caa55
#define LIST_95a94c0379b44bd3967523c81d4caa55
#include <stdbool.h>
#include <stddef.h>
#include "exception.h"
#include "object.h"

/** Represents a list of objects that can be accessed by index. */
struct List
{
    void* items;
    size_t itemSize;
    size_t count;
    size_t capacity;
};

/** Represents a list of objects that can be accessed by index. */
typedef struct List* List;

/**
 * Initializes a `List` instance.
 *
 * @param instance the `List` instance.
 * @param itemSize the size of each element in the list.
 * @param capacity the required minimum capacity.
 * @return `EXCEPTION_OUT_OF_MEMORY` if there is not enough memory to complete
 *         the operation; otherwise `0`.
*/
Exception list(List instance, size_t itemSize, size_t capacity);

/**
 * Adds an item to the end of the list.
 *
 * @param instance the `List` instance.
 * @param item     the item to add.
 * @return An exception; otherwise `0`. This method always returns `0` if the
 *         current capacity is sufficient.
*/
Exception list_add(List instance, Object item);

/**
 * Ensures that the capacity of this list is at least the specified capacity.
 * If the current capacity is less than the required minimum capacity, it is
 * increased to at least the specified capacity.
 *
 * @param instance the `List` instance.
 * @param capacity the required minimum capacity.
 * @return `EXCEPTION_OUT_OF_MEMORY` if there is not enough memory to complete
 *         the operation; otherwise `0`.
*/
Exception list_ensure_capacity(List instance, size_t capacity);

/**
 * Removes all elements from the list.
 *
 * @param instance the `List` instance.
*/
void list_clear(List instance);

/**
 * Frees all resources.
 *
 * @param instance the `List` instance. This method corrupts the `instance`
 *                 argument.
*/
void finalize_list(List instance);

#endif
