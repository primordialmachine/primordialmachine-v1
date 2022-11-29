#if !defined(RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_S32_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_S32_H_INCLUDED

#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Multiply_X64_multiply_s32
  (
    int32_t x,
    int32_t y,
    int32_t *z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_S32_H_INCLUDED
