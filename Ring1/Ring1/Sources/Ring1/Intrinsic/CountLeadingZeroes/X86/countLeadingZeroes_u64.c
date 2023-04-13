// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u64.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u64.h"

#include "Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u32.h"

short
Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u64
  (
    uint64_t x
  )
{
  uint32_t hi = (x & 0xffffffff00000000) >> 32;
  uint32_t lo = (x & 0x00000000ffffffff) >> 0;
  if (hi) {
    return Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u32(hi);
  } else {
    return 32 + Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u32(lo);
  }
}
