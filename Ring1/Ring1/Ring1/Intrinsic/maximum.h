// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/maximum.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

#if !defined(RING1_INTRINSIC_MAXIMUM_H_INCLUDED)
#define RING1_INTRINSIC_MAXIMUM_H_INCLUDED

#include <inttypes.h>
#include "Ring1/Result.h"

#define IMPLEMENTATION(SUFFIX, TYPE) \
  Ring1_Result Ring1_Intrinsic_maximum_##SUFFIX(TYPE* result, TYPE const x, TYPE const y);

IMPLEMENTATION(f32, float)

IMPLEMENTATION(f64, double)

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

#endif // RING1_INTRINSIC_MAXIMUM_H_INCLUDED
