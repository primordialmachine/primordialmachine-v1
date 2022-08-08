// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Runtime/PrimitiveTypes.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/PrimitiveTypes.h"

#include "Ring2/_Include.h"
#include "Ring1/Status.h"
#include <stdio.h>
#include "Ring1/Hash.h"

Ring1_CheckReturn() Ring2_Integer
Machine_ForeignProcedure_getHashValue
  (
    Ring2_Context *context,
    Machine_ForeignProcedure* x
  )
{
  int64_t temporary;
  Ring1_Hash_toI64_p(&temporary, x);
  return temporary;
}

Ring1_CheckReturn() Ring2_Boolean
Machine_ForeignProcedure_isEqualTo
  (
    Ring2_Context *context,
    Machine_ForeignProcedure* x,
    Machine_ForeignProcedure* y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_String *
Machine_ForeignProcedure_toString
  (
    Ring2_Context *context,
    Machine_ForeignProcedure *x
  )
{
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%p", x);
  if (n < 0 || n > 1024 + 1) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  return Ring2_String_create(buffer, (size_t)n);
}
