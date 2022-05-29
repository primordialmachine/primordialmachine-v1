// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Boolean.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Operations/Boolean.h"

#include "Ring1/Hash.h"

Ring1_CheckReturn() Ring2_Integer
Ring2_Boolean_getHashValue
  (
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
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isEqualTo
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isNotEqualTo
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return !Ring2_Boolean_isEqualTo(x, y); }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isLowerThan
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x < y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isLowerThanOrEqualTo
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x <= y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isGreaterThan
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x > y;}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isGreaterThanOrEqualTo
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x >= y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_and
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x && y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_or
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  )
{ return x || y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_affirmate
  (
    Ring2_Boolean x
  )
{ return x; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_negate
  (
    Ring2_Boolean x
  )
{ return !x; }
