#if !defined(MKX_INTRINSIC_COUNTLEADINGZEROES_H_INCLUDED)
#define MKX_INTRINSIC_COUNTLEADINGZEROES_H_INCLUDED

#include <inttypes.h>
#include "Ring1/Intrinsic/CheckReturn.h"
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

#endif // MKX_INTRINSIC_COUNTLEADINGZEROES_H_INCLUDED