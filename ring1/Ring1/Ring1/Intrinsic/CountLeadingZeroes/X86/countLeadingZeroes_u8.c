// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u8.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u8.h"

short
Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u8
  (
    uint8_t x
  )
{
    // Maps a value from 0000 (0x0) to 1111 (0xf) the value's number of leading bits.
    static const short lookup[16] =
    {
      4, //  0: 0000
      3, //  1: 0001
      2, //  2: 0010
      2, //  3: 0011
      1, //  4: 0100
      1, //  5: 0101
      1, //  6: 0110
      1, //  7: 0111
      0, //  8: 1000
      0, //  9: 1001
      0, // 10: 1010
      0, // 11: 1011
      0, // 12: 1100
      0, // 13: 1101
      0, // 14: 1110
      0, // 15: 1111
    };
    uint8_t upper = (x & 0xf0) >> 4;
    uint8_t lower = (x & 0x0f) >> 0;
    return upper ? lookup[upper] : 4 + lookup[lower];
}
