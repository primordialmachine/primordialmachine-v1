// Copyright (c) 2023 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/sin.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/sin.h"
#undef RING3_MATH_PRIVATE

#include <math.h>

Ring1_NoDiscardReturn() Ring2_Real64
Ring3_Math_sinf64
  (
    Ring2_Real64 x
  )
{ return sin(x); }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_sinf32
  (
    Ring2_Real32 x
  )
{ return sinf(x); }
