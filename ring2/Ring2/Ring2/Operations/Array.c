// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Array.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/Array.h"

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

#include "Ring1/Status.h"

Ring1_CheckReturn() Ring2_Boolean
Ring2_Array_isEqualTo
  (
    Ring2_Context* context,
    Ring2_Array const* x,
    Ring2_Array const* y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Array_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_Array const* x,
    Ring2_Array const* y
  )
{ return x != y; }

Ring1_CheckReturn() Ring2_String*
Ring2_Array_toString
  (
    Ring2_Context* context,
    Ring2_Array* self
  )
{ return Ring2_ArrayModule_toString(context, self); }

#endif
