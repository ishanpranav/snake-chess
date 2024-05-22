// list.c
// Copyright (c) 2024 Ishan Pranav
// Licensed under the MIT license.

// Retrieved from https://github.com/ishanpranav/codebook

// https://github.com/ishanpranav/codebook/blob/master/lib/list.c

#include <stdlib.h>
#include <string.h>
#include "euler.h"
#include "list.h"
#include "object.h"

Exception list(List instance, size_t itemSize, size_t capacity)
{
    if (capacity < 4)
    {
        capacity = 4;
    }

    instance->items = malloc(capacity * itemSize);

    if (!instance->items)
    {
        return EXCEPTION_OUT_OF_MEMORY;
    }

    instance->itemSize = itemSize;
    instance->count = 0;
    instance->capacity = capacity;

    return 0;
}

Exception list_ensure_capacity(List instance, size_t capacity)
{
    if (instance->capacity >= capacity)
    {
        return 0;
    }

    size_t newCapacity = instance->capacity * 2;

    if (capacity > newCapacity)
    {
        newCapacity = capacity;
    }

    void* newItems = realloc(instance->items, newCapacity * instance->itemSize);

    if (!newItems)
    {
        return EXCEPTION_OUT_OF_MEMORY;
    }

    instance->capacity = newCapacity;
    instance->items = newItems;

    return 0;
}

Exception list_add(List instance, Object item)
{
    Exception ex = list_ensure_capacity(instance, instance->count + 1);

    if (ex)
    {
        return ex;
    }

    void* end = (char*)instance->items + instance->count * instance->itemSize;

    if (item)
    {
        memcpy(end, item, instance->itemSize);
    }

    instance->count++;

    return 0;
}

void list_clear(List instance)
{
    instance->count = 0;
}

void finalize_list(List instance)
{
    list_clear(instance);
    free(instance->items);

    instance->items = NULL;
    instance->itemSize = 0;
    instance->capacity = 0;
}
