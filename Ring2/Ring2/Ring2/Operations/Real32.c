// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Real32.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Operations/Real32.h"
#undef RING2_PRIVATE


#include <math.h>
#include <stdio.h>
#include "Ring1/Conversion.h"
#include "Ring1/Hash.h"
#include "Ring1/Status.h"
#define RING2_PRIVATE (1)
#include "Ring2/Context.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Operations/_Buffer.h"
#undef RING2_PRIVATE


Ring1_CheckReturn() Ring2_Integer
Ring2_Real32_getHashValue
  (
    Ring2_Context* context,
    Ring2_Real32 x
  )
{
  int64_t temporary;
  Ring1_Hash_toI64_f32(&temporary, x);
  return temporary;
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_getHashEqual
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{
  if (isnan(x) && isnan(y)) {
    return Ring2_Boolean_True;
  } else {
    return x == y;
  }
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isEqualTo
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x != y; } 

void
Ring2_Real32_isLowerThan
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{ Ring2_Value_setBoolean(z, Ring2_Value_getReal32(x) < Ring2_Value_getReal32(y)); }

void
Ring2_Real32_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{ Ring2_Value_setBoolean(z, Ring2_Value_getReal32(x) <= Ring2_Value_getReal32(y)); }

void
Ring2_Real32_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{ Ring2_Value_setBoolean(z, Ring2_Value_getReal32(x) > Ring2_Value_getReal32(y)); }

void
Ring2_Real32_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{ Ring2_Value_setBoolean(z, Ring2_Value_getReal32(x) >= Ring2_Value_getReal32(y)); }

void
Ring2_Real32_add
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{ Ring2_Value_setReal32(z, Ring2_Value_getReal32(x) + Ring2_Value_getReal32(y)); }

void
Ring2_Real32_subtract
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{ Ring2_Value_setReal32(z, Ring2_Value_getReal32(x) - Ring2_Value_getReal32(y)); }

void
Ring2_Real32_multiply
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{ Ring2_Value_setReal32(z, Ring2_Value_getReal32(x) * Ring2_Value_getReal32(y)); }

void
Ring2_Real32_divide
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{ Ring2_Value_setReal32(z, Ring2_Value_getReal32(x) / Ring2_Value_getReal32(y)); }

Ring1_CheckReturn() Ring2_Real32
Ring2_Real32_affirmate
  (
    Ring2_Context* context,
    Ring2_Real32 x
  )
{ return +x; }

Ring1_CheckReturn() Ring2_Real32
Ring2_Real32_negate
  (
    Ring2_Context* context,
    Ring2_Real32 x
  )
{ return -x; }

Ring1_CheckReturn() Ring2_String *
Ring2_Real32_toString
  (
    Ring2_Context *context,
    Ring2_Real32 x
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
      return Ring2_String_create(buffer, result);
    }
    bufferSize = result + 1;
  } while (true);
}

Ring1_CheckReturn() Ring2_Real32
Ring2_Real32_fromString
  (
    Ring2_Context* context,
    Ring2_String* x
  )
{
  const char* start = Ring2_String_getBytes(x),
            * end = Ring2_String_getBytes(x)
                  + Ring2_String_getNumberOfBytes(x);
  Ring2_Real32 value;
  if (Ring1_Conversion_stringToFloat(&value, start, end)) {
    Ring2_jump();
  }
  return value;
}
