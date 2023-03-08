#include "uint64.h"

typedef uint32_t *Xorshift32;

/**
 *
 */
UInt64 xorshift32_next(Xorshift32 this);

/**
 *
 */
UInt64 xorshift32_next_pseudolegal(Xorshift32 this);
