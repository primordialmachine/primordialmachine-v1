// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/ForeignProcedure.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

#define RING2_INTERNAL (1)
#include "Ring2/Types/ForeignProcedure.h"

#include "Ring1/Hash.h"
#include "Ring1/Status.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Types/String.h"
#include <stdio.h>

Ring1_CheckReturn() int64_t
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

Ring1_CheckReturn() bool
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
  return Ring2_String_create(Ring2_Context_get(), buffer, (size_t)n);
}
