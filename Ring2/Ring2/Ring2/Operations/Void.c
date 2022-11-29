// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Void.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Operations/Void.h"
#undef RING2_PRIVATE


#define RING2_PRIVATE (1)
#include "Ring2/Context.h"
#undef RING2_PRIVATE


Ring1_CheckReturn() Ring2_Integer
Ring2_Void_getHashValue
  (
    Ring2_Context* context,
    Ring2_Void x
  )
{
  // 1249  is merely one positive and sufficiently big prime number.
  return 1249;
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_getHashEqual
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  )
{ return Ring2_Boolean_True; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isEqualTo
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  )
{ return Ring2_Boolean_True; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  )
{ return !Ring2_Void_isEqualTo(context, x, y); }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isLowerThan
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  )
{ return false; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  )
{ return true; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  )
{ return false; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  )
{ return true; }

Ring1_CheckReturn() Ring2_String *
Ring2_Void_toString
  (
    Ring2_Context *context,
    Ring2_Void x
  )
{
  static char const* bytes = "void";
  static size_t const numberOfBytes = sizeof("void") - 1;
  return Ring2_String_create(bytes, numberOfBytes);
}
