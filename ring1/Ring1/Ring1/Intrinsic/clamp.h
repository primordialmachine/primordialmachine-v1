// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/clamp.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_CLAMP_H_INCLUDED)
#define RING1_INTRINSIC_CLAMP_H_INCLUDED

#include <inttypes.h>
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

#define IMPLEMENTATION(SUFFIX, TYPE) \
  Ring1_CheckReturn() Ring1_Result \
  Ring1_Intrinsic_clamp_##SUFFIX \
    ( \
      TYPE* result, \
      TYPE x, \
      TYPE minimum, \
      TYPE maximum \
    );

IMPLEMENTATION(f32, float)

IMPLEMENTATION(f64, double)

IMPLEMENTATION(u8, uint8_t)

IMPLEMENTATION(s8, int8_t)

IMPLEMENTATION(u16, uint16_t)

IMPLEMENTATION(s16, int16_t)

IMPLEMENTATION(u32, uint32_t)

IMPLEMENTATION(s32, int32_t)

IMPLEMENTATION(u64, uint64_t)

IMPLEMENTATION(s64, int64_t)

IMPLEMENTATION(sz, size_t)

#undef IMPLEMENTATION

#endif // RING1_INTRINSIC_CLAMP_H_INCLUDED
