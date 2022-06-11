// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Real32.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Operations/Real32.h"

#include "Ring1/Hash.h"
#include <math.h>

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

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isLowerThan
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x < y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x <= y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x > y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x >= y; }

Ring1_CheckReturn() Ring2_Real32
Ring2_Real32_add
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x + y; }

Ring1_CheckReturn() Ring2_Real32
Ring2_Real32_subtract
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x - y; }

Ring1_CheckReturn() Ring2_Real32
Ring2_Real32_multiply
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x * y; }

Ring1_CheckReturn() Ring2_Real32
Ring2_Real32_divide
  (
    Ring2_Context* context,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{ return x / y; }

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
