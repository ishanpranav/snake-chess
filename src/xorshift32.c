#include "xorshift32.h"
#include "uint64.h"
#define MASK_UINT16 0xffff

UInt64 xorshift32_next(Xorshift32 this)
{
    UInt64 result = *this;

    result ^= result << 13;
    result ^= result >> 17;
    result ^= result << 5;
    *this = result;

    return result;
}

UInt64 random_next_pseudolegal(Xorshift32 this)
{
    return ((UInt64)(random_next(this)) & MASK_UINT16) |
           ((UInt64)(random_next(this)) & MASK_UINT16 << 16) |
           ((UInt64)(random_next(this)) & MASK_UINT16 << 32) |
           ((UInt64)(random_next(this)) & MASK_UINT16 << 48);
}
