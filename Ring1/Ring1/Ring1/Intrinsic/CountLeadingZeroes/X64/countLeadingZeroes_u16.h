// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/CountLeadingZeroes/X64/countLeadingZeroes_u16.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_COUNTLEADINGZEROES_X64_COUNTLEADINGZEROES_U16_H_INCLUDED)
#define RING1_INTRINSIC_COUNTLEADINGZEROES_X64_COUNTLEADINGZEROES_U16H_INCLUDED

#include <inttypes.h>

#if defined(_MSC_VER) && defined(_WIN64)

short
Ring1_Intrinsic_CountLeadingZeroes_X64_countLeadingZeroes_u16
  (
    uint16_t x
  );

#endif

#endif // RING1_INTRINSIC_COUNTLEADINGZEROES_X64_COUNTLEADINGZEROES_U16_H_INCLUDED
