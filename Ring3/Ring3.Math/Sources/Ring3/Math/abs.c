// Copyright (c) 2023 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/abs.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/abs.h"
#undef RING3_MATH_PRIVATE

#include <math.h>

Ring1_NoDiscardReturn() Ring2_Real64
Ring3_Math_absf64
  (
    Ring2_Real64 x
  )
{ return fabs(x); }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_absf32
  (
    Ring2_Real32 x
  )
{ return fabsf(x); }
