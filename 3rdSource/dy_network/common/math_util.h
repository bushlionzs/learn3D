#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__
#include <stdint.h>
static inline int
is_pow_of_2(uint32_t x) {
    return !(x & (x - 1));
}

static inline uint32_t
next_pow_of_2(uint32_t x) {
    if (x > 0x80000000)
        return 0x80000000;

    if (is_pow_of_2(x))
        return x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}
#endif //__MATH_UTIL_H__