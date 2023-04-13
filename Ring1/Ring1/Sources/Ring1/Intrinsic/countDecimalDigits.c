// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/countDecimalDigits.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_PRIVATE (1)
#include "Ring1/Intrinsic/countDecimalDigits.h"
#undef RING_PRIVATE

Ring1_NoDiscardReturn() uint8_t
Ring1_countDecimalDigits_u8
  (
    uint8_t value
  )
{
  if (value == 0) {
    return 1;
  } else {
    uint8_t n = 0;
    do {
      value /= 10;
      n++;
    } while (value);
    return n;
  }
}
  
Ring1_NoDiscardReturn() uint8_t
Ring1_countDecimalDigits_u16
  (
    uint16_t value
  )
{
  if (value == 0) {
    return 1;
  } else {
    uint8_t n = 0;
    do {
      value /= 10;
      n++;
    } while (value);
    return n;
  }  
}
  
Ring1_NoDiscardReturn() uint8_t
Ring1_countDecimalDigits_u32
  (
    uint32_t value
  )
{
  if (value == 0) {
    return 1;
  } else {
    uint8_t n = 0;
    do {
      value /= 10;
      n++;
    } while (value);
    return n;
  }  
}

Ring1_NoDiscardReturn() uint8_t
Ring1_countDecimalDigits_u64
  (
    uint64_t value
  )
{
  if (value == 0) {
    return 1;
  } else {
    uint8_t n = 0;
    do {
      value /= 10;
      n++;
    } while (value);
    return n;
  }  
}
