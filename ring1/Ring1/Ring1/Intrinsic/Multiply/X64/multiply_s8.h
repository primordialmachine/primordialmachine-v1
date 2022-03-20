#if !defined(RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_S8_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_S8_H_INCLUDED

#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Multiply_X64_multiply_s8
  (
    int8_t x,
    int8_t y,
    int8_t *z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_S8_H_INCLUDED
