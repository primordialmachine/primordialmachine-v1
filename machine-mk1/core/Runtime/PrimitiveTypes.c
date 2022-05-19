/// @file Runtime/PrimitiveTypes.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/PrimitiveTypes.h"

#include "Runtime/Assertions.h"
#include "Ring2/JumpTargetModule.h"
#include "Ring2/Operations.h"
#include "Runtime/Status.h"
#include "Runtime/String.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Ring1/Hash.h"

int64_t Machine_hashPointer_i64(void const* x) {
  int64_t temporary;
  Ring1_Hash_toI64_p(&temporary, x);
  return temporary;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_CheckReturn() Machine_Integer
Machine_Boolean_getHashValue
  (
    Machine_Boolean x
  )
{ return Ring2_Boolean_getHashValue(x); }

Ring1_CheckReturn() Machine_Boolean
Machine_Boolean_isEqualTo
  (
    Machine_Boolean x,
    Machine_Boolean y
  )
{ return Ring2_Boolean_isEqualTo(x, y); }

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
    Ring2_jump();
  }
  return Machine_String_create(buffer, (size_t)n);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_CheckReturn() Machine_Integer
Machine_Integer_getHashValue
  (
    Machine_Integer x
  )
{ return Ring2_Integer_getHashValue(x); }

Ring1_CheckReturn() Machine_Boolean
Machine_Integer_isEqualTo
  (
    Machine_Integer x,
    Machine_Integer y
  )
{ return Ring2_Integer_isEqualTo(x, y); }

Machine_String* Machine_Integer_toString(Machine_Integer x) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%" PRIu64, x);
  if (n < 0 || n > 1024 + 1) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Ring2_jump();
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

Ring1_CheckReturn() Machine_Integer
Machine_Real_getHashValue
  (
    Machine_Real x
  )
{ return Ring2_Real32_getHashValue(x); }

Ring1_CheckReturn() Machine_Boolean
Machine_Real_isEqualTo
  (
    Machine_Real x,
    Machine_Real y
  )
{ return Ring2_Real32_isEqualTo(x, y); }

Machine_String* Machine_Real_toString(Machine_Real x) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%g", x);
  if (n < 0 || n > 1024 + 1) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Ring2_jump();
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

Ring1_CheckReturn() Machine_Integer
Machine_Void_getHashValue
  (
    Machine_Void x
  )
{ return Ring2_Void_getHashValue(x); }

Ring1_CheckReturn() Machine_Boolean
Machine_Void_isEqualTo
  (
    Machine_Void x,
    Machine_Void y
  )
{ return Ring2_Void_isEqualTo(x, y); }

Machine_String* Machine_Void_toString(Machine_Void x) {
  return Machine_String_create("void", strlen("void"));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
