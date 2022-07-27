/// @file Runtime/PrimitiveTypes.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/PrimitiveTypes.h"

#include "Runtime/Assertions.h"
#include "Ring2/_Include.h"
#include "Ring1/Status.h"
#include "Runtime/String.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Ring1/Hash.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_String* Machine_Boolean_toString(Ring2_Boolean value) {
  return value ? Machine_String_create("true", strlen("true"))
               : Machine_String_create("false", strlen("false"));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_Integer Machine_ForeignProcedure_getHashValue(Machine_ForeignProcedure* x) {
  int64_t temporary;
  Ring1_Hash_toI64_p(&temporary, x);
  return temporary;
}

Ring2_Boolean Machine_ForeignProcedure_isEqualTo(Machine_ForeignProcedure* x,
                                                 Machine_ForeignProcedure* y) {
  return x == y;
}

Ring2_String* Machine_ForeignProcedure_toString(Machine_ForeignProcedure* x) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%p", x);
  if (n < 0 || n > 1024 + 1) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  return Machine_String_create(buffer, (size_t)n);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_String* Machine_Integer_toString(Ring2_Integer x) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%" PRIu64, x);
  if (n < 0 || n > 1024 + 1) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  return Machine_String_create(buffer, (size_t)n);
}

Ring2_Integer Machine_Integer_compareTo(Ring2_Integer x, Ring2_Integer y) {
  if (x < y)
    return -1;
  else if (x > y)
    return +1;
  else
    return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_String* Machine_Real_toString(Ring2_Real32 x) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%g", x);
  if (n < 0 || n > 1024 + 1) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  return Machine_String_create(buffer, (size_t)n);
}

Ring2_Integer Machine_Real_compareTo(Ring2_Real32 x, Ring2_Real32 y) {
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

Ring2_String* Machine_Void_toString(Ring2_Void x) {
  return Machine_String_create("void", strlen("void"));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
