// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/lerp.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_LERP_H_INCLUDED)
#define RING1_INTRINSIC_LERP_H_INCLUDED

#include "Ring1/Intrinsic/clamp.h"

float
Mkx_Intrinsic_lerp_f32
  (
    float t,
    float x,
    float y
  );

double
Mkx_Intrinsic_lerp_f64
  (
    double t,
    double x,
    double y
  );

#endif // RING1_INTRINSIC_LERP_H_INCLUDED
