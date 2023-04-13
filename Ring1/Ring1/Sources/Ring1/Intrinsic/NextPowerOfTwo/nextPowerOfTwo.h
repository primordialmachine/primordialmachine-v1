#if !defined(RING1_INTRINSIC_NEXTPOWEROFTWO_H_INCLUDED)
#define RING1_INTRINSIC_NEXTPOWEROFTWO_H_INCLUDED

#include <stdint.h>
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_s8
  (
    int8_t *result,
    int8_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_u8
  (
    uint8_t *result,
    uint8_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_s16
  (
    int16_t *result,
    int16_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_u16
  (
    uint16_t *result,
    uint16_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_s32
  (
    int32_t *result,
    int32_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_u32
  (
    uint32_t *result,
    uint32_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_s64
  (
    int64_t *result,
    int64_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_u64
  (
    uint64_t *result,
    uint64_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_sz
  (
    size_t *result,
    size_t x
  );

#endif // RING1_INTRINSIC_NEXTPOWEROFTWO_H_INCLUDED
