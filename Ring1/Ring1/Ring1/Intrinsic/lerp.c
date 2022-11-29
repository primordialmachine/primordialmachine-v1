// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/lerp.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/lerp.h"

#include "Ring1/Intrinsic/clamp.h"

float
Mkx_Intrinsic_lerp_f32
  (
    float t,
    float x,
    float y
  )
{
  Ring1_Intrinsic_clamp_f32(&t, t, 0.0f, 1.0f);
  return (1.f - t) * x + t * y;
}

double
Mkx_Intrinsic_lerp_f64
  (
    double t,
    double x,
    double y
  )
{
  Ring1_Intrinsic_clamp_f64(&t, t, 0.0, 1.0);
  return (1. - t) * x + t * y;
}
