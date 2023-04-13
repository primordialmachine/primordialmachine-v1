// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u8.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_COUNTLEADINGZEROES_X86_COUNTLEADINGZEROES_U8_H_INCLUDED)
#define RING1_INTRINSIC_COUNTLEADINGZEROES_X86_COUNTLEADINGZEROES_U8_H_INCLUDED

#include <inttypes.h>

#if defined(_MSC_VER) && !defined(_WIN64) && defined(_WIN32)

short
Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u8
  (
    uint8_t x
  );

#endif

#endif // RING1_INTRINSIC_COUNTLEADINGZEROES_X86_COUNTLEADINGZEROES_U8_H_INCLUDED
