// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Real64.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Operations/Real64.h"

#include "Ring1/Hash.h"
#include <math.h>

Ring1_CheckReturn() Ring2_Integer
Ring2_Real64_getHashValue
  (
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
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isNotEqualTo
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x != y; } 

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isLowerThan
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x < y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isLowerThanOrEqualTo
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x <= y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isGreaterThan
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x > y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isGreaterThanOrEqualTo
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  )
{ return x >= y; }
