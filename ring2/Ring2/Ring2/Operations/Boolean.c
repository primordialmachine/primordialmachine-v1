// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Boolean.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/Boolean.h"


#include "Ring2/Context.h"
#include "Ring1/Conversion.h"
#include "Ring1/Hash.h"
#include "Ring2/JumpTarget.h"


Ring1_CheckReturn() Ring2_Integer
Ring2_Boolean_getHashValue
  (
    Ring2_Context *context,
    Ring2_Boolean x
  )
{
  int64_t temporary;
  Ring1_Hash_toI64_b(&temporary, x);
  return temporary;
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_getHashEqual
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isEqualTo
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isNotEqualTo
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return !Ring2_Boolean_isEqualTo(context, x, y); }

void
Ring2_Boolean_isLowerThan
  (
    Ring2_Context *context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{
  Ring2_Value_setBoolean(z, Ring2_Value_getBoolean(x) < Ring2_Value_getBoolean(y));
}

void
Ring2_Boolean_isLowerThanOrEqualTo
  (
    Ring2_Context *context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{
  Ring2_Value_setBoolean(z, Ring2_Value_getBoolean(x) <= Ring2_Value_getBoolean(y));
}

void
Ring2_Boolean_isGreaterThan
  (
    Ring2_Context *context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{
  Ring2_Value_setBoolean(z, Ring2_Value_getBoolean(x) > Ring2_Value_getBoolean(y));
}

void
Ring2_Boolean_isGreaterThanOrEqualTo
  (
    Ring2_Context *context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{
  Ring2_Value_setBoolean(z, Ring2_Value_getBoolean(x) >= Ring2_Value_getBoolean(y));
}

void
Ring2_Boolean_and
  (
    Ring2_Context *context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{
  Ring2_Value_setBoolean(z, Ring2_Value_getBoolean(x) && Ring2_Value_getBoolean(y));
}

void
Ring2_Boolean_or
  (
    Ring2_Context *context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{
  Ring2_Value_setBoolean(z, Ring2_Value_getBoolean(x) || Ring2_Value_getBoolean(y));
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_affirmate
  (
    Ring2_Context *context,
    Ring2_Boolean x
  )
{ return x; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_negate
  (
    Ring2_Context *context,
    Ring2_Boolean x
  )
{ return !x; }

Ring1_CheckReturn() Ring2_String*
Ring2_Boolean_toString
  (
    Ring2_Context* context,
    Ring2_Boolean x
  )
{
  if (x) {
    static char const* bytes = "true";
    static size_t const numberOfBytes = sizeof("true") - 1;
    return Ring2_String_create(Ring2_Context_get(), bytes, numberOfBytes);
  } else {
    static char const* bytes = "false";
    static size_t const numberOfBytes = sizeof("false") - 1;
    return Ring2_String_create(Ring2_Context_get(), bytes, numberOfBytes);
  }
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_fromString
  (
    Ring2_Context* context,
    Ring2_String* w
  )
{
  char const* start = Ring2_String_getBytes(Ring2_Context_get(), w),
            * end = Ring2_String_getBytes(Ring2_Context_get(), w)
                  + Ring2_String_getNumberOfBytes(Ring2_Context_get(), w);
  bool v;
  if (Ring1_Conversion_stringToBool(&v, start, end)) {
    Ring2_jump();
  }
  return v;
}
