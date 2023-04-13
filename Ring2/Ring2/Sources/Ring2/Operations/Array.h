// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Array.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_ARRAY_H_INCLUDED)
#define RING2_OPERATIONS_ARRAY_H_INCLUDED


#if !defined(RING2_PRIVATE) || 1 != RING2_PRIVATE
#error("Do not include `Ring2/Operations/Array.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

#include "Ring2/Types.h"
#include "Ring2/Types/Value.h"

Ring1_CheckReturn() Ring2_Boolean
Ring2_Array_isEqualTo
  (
    Ring2_Context* context,
    Ring2_Array const* x,
    Ring2_Array const* y
  );

Ring1_CheckReturn() Ring2_Boolean
Ring2_Array_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_Array const* x,
    Ring2_Array const* y
  );

Ring1_CheckReturn() Ring2_Value
Ring2_Array_getElement
  (
    Ring2_Context* context,
    Ring2_Array* self,
    Ring2_Integer index
  );

void
Ring2_Array_setElement
  (
    Ring2_Context* context,
    Ring2_Array* self,
    Ring2_Integer index,
    Ring2_Value value
  );

Ring1_CheckReturn() Ring2_Integer
Ring2_Array_getLength
  (
    Ring2_Context* context,
    Ring2_Array* self
  );

Ring1_CheckReturn() Ring2_String*
Ring2_Array_toString
  (
    Ring2_Context* context,
    Ring2_Array* self
  );

#endif // Ring2_Configuration_withArray

#endif // RING2_OPERATIONS_ARRAY_H_INCLUDED
