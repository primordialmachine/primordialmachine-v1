/// @file Runtime/PrimitiveTypes.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/PrimitiveTypes.h"

#include <math.h>
#include <float.h>

size_t Machine_Real_getHashValue(Machine_Real x) {
  switch (fpclassify(x)) {
  case FP_INFINITE:
  { return x > 0.0f ? 7 : 11; }
  case FP_NAN:
  { return 13; };
  case FP_ZERO:
  { return 17; }
  case FP_NORMAL:
  case FP_SUBNORMAL:
  default: // The default case handles the case when fpclassify may return an implementation defined type gracefully.
  {
    if (x == 0.0f) x = +0.0f; // +0.0f == -0.0f. Hence, map both to +0.0f.
    typedef union Bits {
      uint32_t u32;
      float f32;
    } Bits;
    Bits bits;
    bits.f32 = x;
    return bits.u32;
  }
  };
}

bool Machine_Real_isEqualTo(Machine_Real x, Machine_Real y) {
  if (isnan(x) && isnan(y)) return true;
  return x == y;
}
