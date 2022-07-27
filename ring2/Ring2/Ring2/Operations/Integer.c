// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Integer.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/Integer.h"

#include "Ring1/Hash.h"

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

Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isLowerThan
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return x < y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return x <= y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return x > y;}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return x >= y; }

Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_add
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return x + y; }

Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_subtract
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return x - y; }

Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_multiply
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return x * y; }

Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_divide
  (
    Ring2_Context* context,
    Ring2_Integer x,
    Ring2_Integer y
  )
{ return x / y; }

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
