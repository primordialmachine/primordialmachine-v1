// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/ForeignFunction.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/ForeignFunction.h"

#include "Ring1/Status.h"
#include "Ring1/Hash.h"
#include "Ring2/JumpTarget.h"
#include <stdio.h>

Ring1_CheckReturn() Ring2_Boolean
Ring2_ForeignFunction_isEqualTo
  (
    Ring2_Context* context,
    Ring2_ForeignFunction* x,
    Ring2_ForeignFunction* y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_ForeignFunction_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_ForeignFunction* x,
    Ring2_ForeignFunction* y
  )
{ return x != y; }

Ring1_CheckReturn() Ring2_Integer
Ring2_ForeignFunction_getHashValue
  (
    Ring2_Context* context,
    Ring2_ForeignFunction *x
  )
{
  int64_t temporary;
  Ring1_Hash_toI64_p(&temporary, x);
  return temporary;
}

Ring1_CheckReturn() Ring2_String *
Ring2_ForeignProcedure_toString
  (
    Ring2_Context *context,
    Ring2_ForeignFunction *x
  )
{
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%p", x);
  if (n < 0 || n > 1024 + 1) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    Ring2_jump();
  }
  return Ring2_String_create(Ring2_Context_get(), buffer, (size_t)n);
}

