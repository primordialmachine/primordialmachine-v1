#if !defined(RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_S64_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_S64_H_INCLUDED

#include <inttypes.h>

#if defined(_M_X64)

char
Ring1_Intrinsic_Multiply_X64_multiply_s64
  (
    int64_t x,
    int64_t y,
    int64_t* z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X64_MULTIPLY_S64_H_INCLUDED
