// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/CountLeadingZeroes/x86/countLeadingZeroes_u16.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u16.h"

#include "Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u8.h"

short
Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u16
  (
    uint16_t x
  )
{
  uint16_t t;
  t = (x & 0xff00) >> 8;
  if (t) return Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u8((uint8_t)t);
  t = (x & 0x00ff) >> 0;
  return 8 + Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u8((uint8_t)t);
}
