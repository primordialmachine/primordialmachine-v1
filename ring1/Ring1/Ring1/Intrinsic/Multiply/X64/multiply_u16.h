#if !defined(RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_U16_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_U16_H_INCLUDED

#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Multiply_X64_multiply_u16
  (
    uint16_t x,
    uint16_t y,
    uint16_t* z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_U16_H_INCLUDED
