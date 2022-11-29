// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/CountLeadingZeroes/X64/countLeadingZeroes_u32.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/CountLeadingZeroes/X64/countLeadingZeroes_u32.h"

#include <intrin.h>

short
Ring1_Intrinsic_CountLeadingZeroes_X64_countLeadingZeroes_u32
  (
    uint32_t x
  )
{
  unsigned long n;
  if (_BitScanReverse(&n, x)) {
    // x was not zero.
    return (short)32 - ((short)n + 1);
  } else {
    // x was zero.
    return (short)32;
  }
}
