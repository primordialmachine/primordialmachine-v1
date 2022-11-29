#if !defined(RING1_INTRINSIC_COUNTLEADINGZEROES_H_INCLUDED)
#define RING1_INTRINSIC_COUNTLEADINGZEROES_H_INCLUDED

#include <inttypes.h>
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_countLeadingZeroes_u8
  (
    short* result,
    uint8_t x
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_countLeadingZeroes_u16
  (
    short* result,
    uint16_t x
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_countLeadingZeroes_u32
  (
    short *result,
    uint32_t x
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_countLeadingZeroes_u64
  (
    short *result,
    uint64_t x
  );

#endif // RING1_INTRINSIC_COUNTLEADINGZEROES_H_INCLUDED
