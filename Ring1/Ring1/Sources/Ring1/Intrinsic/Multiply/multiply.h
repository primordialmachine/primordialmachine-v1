#if !defined(RING1_INTRINSIC_MULTIPLY_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_H_INCLUDED

#include <inttypes.h>
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_multiply_s8
  (
    int8_t *result,
    int8_t x,
    int8_t y
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_multiply_u8
  (
    uint8_t *result,
    uint8_t x,
    uint8_t y
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_multiply_s16
  (
    int16_t *result,
    int16_t x,
    int16_t y
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_multiply_u16
  (
    uint16_t *result,
    uint16_t x,
    uint16_t y
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_multiply_s32
  (
    int32_t *result,
    int32_t x,
    int32_t y
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_multiply_u32
  (
    uint32_t *result,
    uint32_t x,
    uint32_t y
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_multiply_s64
  (
    int64_t *result,
    int64_t x,
    int64_t y
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_multiply_u64
  (
    uint64_t *result,
    uint64_t x,
    uint64_t y
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_multiply_sz
  (
    size_t *result,
    size_t x,
    size_t y
  );

#endif // RING1_INTRINSIC_MULTIPLY_H_INCLUDED
