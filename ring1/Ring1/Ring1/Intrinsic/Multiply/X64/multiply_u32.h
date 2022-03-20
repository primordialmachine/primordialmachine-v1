#if !defined(RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_U32_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_U32_H_INCLUDED

#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Multiply_X64_multiply_u32
  (
    uint32_t x,
    uint32_t y,
    uint32_t* z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_U32_H_INCLUDED
