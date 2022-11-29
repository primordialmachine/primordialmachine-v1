#include "Ring1/Intrinsic/Multiply/X64/multiply_u64.h"

#if defined(_M_X64)

#include <intrin.h>

char
Ring1_Intrinsic_Multiply_X64_multiply_u64
  (
    uint64_t x,
    uint64_t y,
    uint64_t* z
  )
{
  uint64_t lo, hi;
  lo = _umul128(x, y, &hi);
  *z = lo;
  return 0 != hi;
}

#endif