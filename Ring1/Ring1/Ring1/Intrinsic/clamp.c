// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/clamp.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/clamp.h"

#include "Ring1/Status.h"
#include <float.h>
#include <math.h>

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_clamp_f32
  (
    float *result,
    float x,
    float minimum,
    float maximum
  )
{ 
  if (!result || isnan(x) || isnan(minimum) || isnan(maximum) ||
      minimum > maximum) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (x < minimum) *result = minimum;
  else if (x > maximum) *result = maximum;
  else *result = x;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_clamp_f64
  (
    double *result,
    double x,
    double minimum,
    double maximum
  )
{
  if (!result || isnan(x) || isnan(minimum) || isnan(maximum) ||
      minimum > maximum) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (x < minimum) *result = minimum;
  else if (x > maximum) *result = maximum;
  else *result = x;
  return Ring1_Result_Success;
}

#define IMPLEMENTATION(SUFFIX,TYPE) \
  Ring1_Result \
  Ring1_Intrinsic_clamp_##SUFFIX \
    ( \
      TYPE* result, \
      TYPE x, \
      TYPE minimum, \
      TYPE maximum \
    ) \
  { \
    if (!result || minimum > maximum) { \
      Ring1_Status_set(Ring1_Status_InvalidArgument); \
      return Ring1_Result_Failure; \
    } \
    if (x < minimum) *result = minimum; \
    else if (x > maximum)  *result = maximum; \
    else *result = x; \
    return Ring1_Result_Success; \
  }

IMPLEMENTATION(u8,uint8_t)

IMPLEMENTATION(s8,int8_t)

IMPLEMENTATION(u16,uint16_t)

IMPLEMENTATION(s16,int16_t)

IMPLEMENTATION(u32,uint32_t)

IMPLEMENTATION(s32,int32_t)

IMPLEMENTATION(u64,uint64_t)

IMPLEMENTATION(s64,int64_t)

IMPLEMENTATION(sz,size_t)

#undef IMPLEMENTATION
