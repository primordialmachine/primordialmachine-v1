// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/ForeignFunction.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Operations/ForeignFunction.h"

Ring1_CheckReturn() Ring2_Boolean
Ring2_ForeignFunction_isEqualTo
  (
    Ring2_Context* context,
    Ring2_ForeignFunction* x,
    Ring2_ForeignFunction* y
  )
{ return x == y; }

Ring1_CheckReturn() Ring2_Boolean
Ring2_ForeignFunction_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_ForeignFunction* x,
    Ring2_ForeignFunction* y
  )
{ return x != y; }
