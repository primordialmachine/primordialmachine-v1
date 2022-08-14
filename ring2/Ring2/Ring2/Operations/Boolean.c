// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Boolean.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/Boolean.h"

#include "Ring1/Intrinsic/Crt.h"
#include "Ring1/Hash.h"

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

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isLowerThan
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x < y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isLowerThanOrEqualTo
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x <= y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isGreaterThan
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x > y;}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isGreaterThanOrEqualTo
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x >= y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_and
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x && y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_or
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x || y; }

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

Ring1_CheckReturn() Ring2_String *
Ring2_Boolean_toString
  (
    Ring2_Context *context,
    Ring2_Boolean value
  )
{
  return value ? Ring2_String_create(Ring2_Context_get(), "true", crt_strlen("true"))
               : Ring2_String_create(Ring2_Context_get(), "false", crt_strlen("false"));
}
