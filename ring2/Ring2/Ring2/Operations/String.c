// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/String.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/String.h"

#include "Ring1/Memory.h"

static int
compareBytes
  (
    Ring2_Context* context,
    Ring2_String const* x,
    Ring2_String const* y
  )
{
  int temporary;
  Ring1_Memory_compare(&temporary,
                       Ring2_String_getBytes(context, x),
                       Ring2_String_getNumberOfBytes(context, x),
                       Ring2_String_getBytes(context, y),
                       Ring2_String_getNumberOfBytes(context, y),
                       Ring1_Memory_Compare_Lexicographic);
  return temporary;
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isEqualTo
  (
    Ring2_Context *context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isNotEqualTo
  (
    Ring2_Context *context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return x != y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isLowerThan
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return compareBytes(context, x, y) < 0; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return compareBytes(context, x, y) <= 0; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return compareBytes(context, x, y) > 0; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  )
{ return compareBytes(context, x, y) >= 0; }
