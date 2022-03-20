#include "Ring1/Intrinsic/Multiply/X86/multiply_s64.h"

#if defined(_M_IX86)

#include <intrin.h>

char
Ring1_Intrinsic_Multiply_X86_multiply_s64
  (
    int64_t x,
    int64_t y,
    int64_t* z
  )
{
  int64_t r = x * y;
  *z = r;
  if (x == INT64_MIN && y == -1)
    return 1;
  if ((y != 0) && (r / y) != x) {
    return 1;
  }
  return 0;
}

#endif
