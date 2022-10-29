// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/ForeignProcedure.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/ForeignProcedure.h"


#include "Ring1/Hash.h"
#include "Ring1/Status.h"

#include "Ring2/Context.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Types/String.h"

#include <stdio.h>


Ring1_CheckReturn() Ring2_Integer
Ring2_ForeignProcedure_getHashValue
  (
    Ring2_Context *context,
    Ring2_ForeignProcedure* x
  )
{
  int64_t temporary;
  Ring1_Hash_toI64_p(&temporary, x);
  return temporary;
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_ForeignProcedure_isEqualTo
  (
    Ring2_Context *context,
    Ring2_ForeignProcedure* x,
    Ring2_ForeignProcedure* y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_ForeignProcedure_isNotEqualTo
  (
    Ring2_Context *context,
    Ring2_ForeignProcedure* x,
    Ring2_ForeignProcedure* y
  )
{ return x != y; }

Ring1_CheckReturn() Ring2_String *
Ring2_ForeignProcedure_toString
  (
    Ring2_Context *context,
    Ring2_ForeignProcedure *x
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
