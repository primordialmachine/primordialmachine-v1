#if !defined(RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_U8_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_U8_H_INCLUDED

#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Multiply_X64_multiply_u8
  (
    uint8_t x,
    uint8_t y,
    uint8_t *z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_U8_H_INCLUDED
