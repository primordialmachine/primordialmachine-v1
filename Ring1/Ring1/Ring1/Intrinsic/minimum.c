// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/minimum.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

#include "Ring1/Intrinsic/minimum.h"

#include "Ring1/Status.h"
#include <float.h>
#include <math.h>

#define IMPLEMENTATION(SUFFIX, TYPE)                                           \
  Ring1_NoDiscardReturn() Ring1_Result                                             \
  Ring1_Intrinsic_minimum_##SUFFIX(TYPE * result, TYPE const x, TYPE const y)  \
  {                                                                            \
    if (!result || isnan(x) || isnan(y)) {                                     \
      Ring1_Status_set(Ring1_Status_InvalidArgument);                          \
      return Ring1_Result_Failure;                                             \
    }                                                                          \
    *result = x < y ? x : y;                                                   \
    return Ring1_Result_Success;                                               \
  }

IMPLEMENTATION(f32, float)

IMPLEMENTATION(f64, double)

#undef IMPLEMENTATION

#define IMPLEMENTATION(SUFFIX, TYPE)                                                               \
  Ring1_NoDiscardReturn() Ring1_Result                                                                 \
  Ring1_Intrinsic_minimum_##SUFFIX(TYPE* result, TYPE const x, TYPE const y)                       \
  {                                                                                                \
    if (!result) {                                                                                 \
      Ring1_Status_set(Ring1_Status_InvalidArgument);                                              \
      return Ring1_Result_Failure;                                                                 \
    }                                                                                              \
    *result = x < y ? x : y;                                                                       \
    return Ring1_Result_Success;                                                                   \
  }

IMPLEMENTATION(sz, size_t)

IMPLEMENTATION(u8, uint8_t)

IMPLEMENTATION(s8, int8_t)

IMPLEMENTATION(u16, uint16_t)

IMPLEMENTATION(s16, int16_t)

IMPLEMENTATION(u32, uint32_t)

IMPLEMENTATION(s32, int32_t)

IMPLEMENTATION(u64, uint64_t)

IMPLEMENTATION(s64, int64_t)

#undef IMPLEMENTATION
