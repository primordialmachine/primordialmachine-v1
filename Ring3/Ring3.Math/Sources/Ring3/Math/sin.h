// Copyright (c) 2023 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/sin.h
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_SIN_H_INCLUDED)
#define RING3_MATH_SIN_H_INCLUDED

#if !defined(RING3_MATH_PRIVATE)
#error("Do not include `Ring3/Math/sin.h` directly, include `Ring3/Math/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"

Ring1_NoDiscardReturn() Ring2_Real64
Ring1_Math_sinf64
  (
    Ring2_Real64 x
  );

Ring1_NoDiscardReturn() Ring2_Real32
Ring1_Math_sinf32
  (
    Ring2_Real32 x
  );

#endif // RING3_MATH_SIN_H_INCLUDED
