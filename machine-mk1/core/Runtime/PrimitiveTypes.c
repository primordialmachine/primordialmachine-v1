/// @file Runtime/PrimitiveTypes.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/PrimitiveTypes.h"

#include "Runtime/Assertions.h"
#include "Runtime/JumpTargetModule.h"
#include "Runtime/Status.h"
#include "Runtime/String.h"
#include <float.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

size_t Machine_hashPointer_sz(void const* x) {
  return (size_t)(uintptr_t)x;
}

int64_t Machine_hashPointer_i64(void const*x) {
#if INT64_MIN >= INTPTR_MIN && INTPTR_MAX <= INT64_MAX
  return (int64_t)(intptr_t)x;
#else
  #error("environment not supported")
#endif
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Machine_Integer Machine_Boolean_getHashValue(Machine_Boolean x) {
  // 1231 and 1237 are merely two positive and sufficiently big prime numbers.
  return x ? 1231 : 1237;
}

Machine_Boolean Machine_Boolean_isEqualTo(Machine_Boolean x, Machine_Boolean y) {
  return x == y;
}

Machine_String* Machine_Boolean_toString(Machine_Boolean value) {
  return value ? Machine_String_create("true", strlen("true"))
               : Machine_String_create("false", strlen("false"));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Machine_Integer Machine_ForeignProcedure_getHashValue(Machine_ForeignProcedure* x) {
  return Machine_hashPointer_i64(x);
}

Machine_Boolean Machine_ForeignProcedure_isEqualTo(Machine_ForeignProcedure* x,
                                                   Machine_ForeignProcedure* y) {
  return x == y;
}

Machine_String* Machine_ForeignProcedure_toString(Machine_ForeignProcedure* x) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%p", x);
  if (n < 0 || n > 1024 + 1) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  return Machine_String_create(buffer, (size_t)n);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Machine_Integer Machine_Integer_getHashValue(Machine_Integer x) {
  return x;
}

Machine_Boolean Machine_Integer_isEqualTo(Machine_Integer x, Machine_Integer y) {
  return x == y;
}

Machine_String* Machine_Integer_toString(Machine_Integer x) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%" PRIu64, x);
  if (n < 0 || n > 1024 + 1) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  return Machine_String_create(buffer, (size_t)n);
}

Machine_Integer Machine_Integer_compareTo(Machine_Integer x, Machine_Integer y) {
  if (x < y)
    return -1;
  else if (x > y)
    return +1;
  else
    return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Machine_Integer Machine_Real_getHashValue(Machine_Real x) {
  switch (fpclassify(x)) {
    case FP_INFINITE: {
      return x > 0.0f ? 7 : 11;
    }
    case FP_NAN: {
      return 13;
    };
    case FP_ZERO: {
      return 17;
    }
    case FP_NORMAL:
    case FP_SUBNORMAL:
    default: // The default case handles the case when fpclassify may return an implementation
             // defined type gracefully.
    {
      if (x == 0.0f)
        x = +0.0f; // +0.0f == -0.0f. Hence, map both to +0.0f.
      typedef union Bits {
        int32_t i32;
        float f32;
      } Bits;
      Bits bits;
      bits.f32 = x;
      return bits.i32;
    }
  };
}

Machine_Boolean Machine_Real_isEqualTo(Machine_Real x, Machine_Real y) {
  return x == y;
}

Machine_String* Machine_Real_toString(Machine_Real x) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%g", x);
  if (n < 0 || n > 1024 + 1) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  return Machine_String_create(buffer, (size_t)n);
}

Machine_Integer Machine_Real_compareTo(Machine_Real x, Machine_Real y) {
  if (isnan(x)) {
    if (isnan(y))
      return 0;
    else
      return -1;
  } else if (isnan(y)) {
    // x is not NaN.
    return +1;
  }
  // Neither x nor y is NaN.
  if (x < y)
    return -1;
  else if (x > y)
    return +1;
  else
    return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Machine_Integer Machine_Void_getHashValue(Machine_Void x) {
  // 1249  is merely one positive and sufficiently big prime number.
  return 1249;
}

Machine_Boolean Machine_Void_isEqualTo(Machine_Void x, Machine_Void y) {
  return Machine_Boolean_True;
}

Machine_String* Machine_Void_toString(Machine_Void x) {
  return Machine_String_create("void", strlen("void"));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
