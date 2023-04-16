// Copyright (c) 2023 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/cos.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/cos.h"
#undef RING3_MATH_PRIVATE

#include <math.h>

Ring1_NoDiscardReturn() Ring2_Real64
Ring1_Math_cosf64
  (
    Ring2_Real64 x
  )
{ return cos(x); }

Ring1_NoDiscardReturn() Ring2_Real32
Ring1_Math_cosf32
  (
    Ring2_Real32 x
  )
{ return cosf(x); }
