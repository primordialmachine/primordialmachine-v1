// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Real64.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/Real64.h"


#include <math.h>
#include <stdio.h>
#include "Ring1/Conversion.h"
#include "Ring1/Hash.h"
#include "Ring1/Status.h"
#include "Ring2/Context.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Operations/_Buffer.h"


Ring1_CheckReturn() Ring2_Integer
Ring2_Real64_getHashValue
  (
    Ring2_Context* context,
    Ring2_Real64 x
  )
{
  int64_t temporary;
  Ring1_Hash_toI64_f64(&temporary, x);
  return temporary;
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_getHashEqual
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{
  if (isnan(x) && isnan(y)) {
    return Ring2_Boolean_True;
  } else {
    return x == y;
  }
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isEqualTo
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x != y; } 

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isLowerThan
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x < y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x <= y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x > y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x >= y; }

Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_add
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x + y; }

Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_subtract
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x - y; }

Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_multiply
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x * y; }

Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_divide
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x / y; }

Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_affirmate
  (
    Ring2_Context* context,
    Ring2_Real64 x
  )
{ return +x; }

Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_negate
  (
    Ring2_Context* context,
    Ring2_Real64 x
  )
{ return -x; }

Ring1_CheckReturn() Ring2_String *
Ring2_Real64_toString
  (
    Ring2_Context *context,
    Ring2_Real64 x
  )
{
  #define DEFAULT_BUFFER_SIZE 20 + 1

  int bufferSize = DEFAULT_BUFFER_SIZE;
  char* buffer;

  do {
    if (Ring2_Operations__Buffer_get(&buffer, bufferSize)) {
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      Ring2_jump();
    }
    int result = snprintf(buffer, bufferSize, "%g", x);
    if (result < 0) {
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    if (bufferSize >= result) {
      return Ring2_String_create(Ring2_Context_get(), buffer, result);
    }
    bufferSize = result + 1;
  } while (true);
}
