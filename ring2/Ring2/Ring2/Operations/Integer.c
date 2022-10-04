// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Integer.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/Integer.h"


#include <math.h>
#include <stdio.h>
#include "Ring1/Conversion.h"
#include "Ring1/Hash.h"
#include "Ring1/Status.h"
#include "Ring2/Context.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Operations/_Buffer.h"


Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_getHashValue
  (
    Ring2_Context* context,
    Ring2_Integer x
  )
{
  int64_t temporary;
  Ring1_Hash_toI64_b(&temporary, x);
  return temporary;
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_getHashEqual
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isEqualTo
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return !Ring2_Integer_isEqualTo(context, x, y); }

void
Ring2_Integer_isLowerThan
  (
    Ring2_Context *context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  )
{
  Ring2_Value_setBoolean(z, Ring2_Value_getInteger(x) < Ring2_Value_getInteger(y));
}

void
Ring2_Integer_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  )
{
  Ring2_Value_setBoolean(z, Ring2_Value_getInteger(x) <= Ring2_Value_getInteger(y));
}

void
Ring2_Integer_isGreaterThan
  (
    Ring2_Context *context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  )
{ 
  Ring2_Value_setBoolean(z, Ring2_Value_getInteger(x) > Ring2_Value_getInteger(y));
}

void
Ring2_Integer_isGreaterThanOrEqualTo
  (
    Ring2_Context *context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  )
{ 
  Ring2_Value_setBoolean(z, Ring2_Value_getInteger(x) >= Ring2_Value_getInteger(y));
}

void
Ring2_Integer_add
  (
    Ring2_Context *context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  )
{
  Ring2_Value_setInteger(z, Ring2_Value_getInteger(x) + Ring2_Value_getInteger(y));
}

void
Ring2_Integer_subtract
  (
    Ring2_Context *context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  )
{
  Ring2_Value_setInteger(z, Ring2_Value_getInteger(x) - Ring2_Value_getInteger(y));
}

void
Ring2_Integer_multiply
  (
    Ring2_Context *context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  )
{
  Ring2_Value_setInteger(z, Ring2_Value_getInteger(x) * Ring2_Value_getInteger(y));
}

void
Ring2_Integer_divide
  (
    Ring2_Context *context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  )
{
  Ring2_Value_setInteger(z, Ring2_Value_getInteger(x) / Ring2_Value_getInteger(y));
}

Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_affirmate
  (
    Ring2_Context* context,
    Ring2_Integer x
  )
{ return +x; }

Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_negate
  (
    Ring2_Context* context,
    Ring2_Integer x
  )
{ return -x; }

Ring1_CheckReturn() Ring2_String *
Ring2_Integer_toString
  (
    Ring2_Context* context,
    Ring2_Integer x
  )
{
  // Maximum value of an int64_t is +9,223,372,036,854,775,807 which are 19 digits and an optional sign.
  // Minimum value of an int64_t is -9,223,372,036,854,775,808 which are 19 digits and a mandatory sign.
  // Hence the maximum length of a string representing an Ring2_Integer is 20 characters.
  #define DEFAULT_BUFFER_SIZE 20 + 1

  int bufferSize = DEFAULT_BUFFER_SIZE;
  char* buffer;
  
  do {
    if (Ring2_Operations__Buffer_get(&buffer, bufferSize)) {
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      Ring2_jump();
    }
    int result = snprintf(buffer, bufferSize, "%" PRId64, x);
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

Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_fromString
  (
    Ring2_Context* context,
    Ring2_String* x
  )
{
  const char* start = Ring2_String_getBytes(Ring2_Context_get(), x),
            * end = Ring2_String_getBytes(Ring2_Context_get(), x)
                  + Ring2_String_getNumberOfBytes(Ring2_Context_get(), x);
  int64_t value;
  if (Ring1_Conversion_stringToInt64(&value, start, end)) {
    Ring2_jump();
  }
  return value;
}
