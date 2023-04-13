#include "Ring1/Intrinsic/Multiply/X64/multiply_s64.h"

#if defined(_M_X64)

#include <intrin.h>
#include <stdbool.h>

char
Ring1_Intrinsic_Multiply_X64_multiply_s64
  (
    int64_t x,
    int64_t y,
    int64_t* z
  )
{
  int64_t lo, hi;
  lo = _mul128(x, y, &hi);
  *z = lo;
  if (x == INT64_MIN && y == -1)
    return 1;
  if ((y != 0) && (lo / y) != x) {
    return 1;
  }
  return 0;
}

#endif
