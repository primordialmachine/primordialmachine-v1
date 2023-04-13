#include "Ring1/Intrinsic/Subtract/subtract.h"

#include "Ring1/Status.h"

#if defined(_M_X64)
  #include "Ring1/Intrinsic/Subtract/X64/subtract_u8.h"
  #include "Ring1/Intrinsic/Subtract/X64/subtract_s8.h"
  #include "Ring1/Intrinsic/Subtract/X64/subtract_u16.h"
  #include "Ring1/Intrinsic/Subtract/X64/subtract_s16.h"
  #include "Ring1/Intrinsic/Subtract/X64/subtract_u32.h"
  #include "Ring1/Intrinsic/Subtract/X64/subtract_s32.h"
  #include "Ring1/Intrinsic/Subtract/X64/subtract_u64.h"
  #include "Ring1/Intrinsic/Subtract/X64/subtract_s64.h"
#elif defined(_M_IX86)
  #include "Ring1/Intrinsic/Subtract/X86/subtract_u8.h"
  #include "Ring1/Intrinsic/Subtract/X86/subtract_s8.h"
  #include "Ring1/Intrinsic/Subtract/X86/subtract_u16.h"
  #include "Ring1/Intrinsic/Subtract/X86/subtract_s16.h"
  #include "Ring1/Intrinsic/Subtract/X86/subtract_u32.h"
  #include "Ring1/Intrinsic/Subtract/X86/subtract_s32.h"
  #include "Ring1/Intrinsic/Subtract/X86/subtract_u64.h"
  #include "Ring1/Intrinsic/Subtract/X86/subtract_s64.h"
#else
  #error("target architecture not supported")
#endif

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_subtract_u8
  (
    uint8_t *result,
    uint8_t x,
    uint8_t y
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  char r = Ring1_Intrinsic_Subtract_X64_subtract_u8(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Subtract_X86_subtract_u8(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_subtract_s8
  (
    int8_t *result,
    int8_t x,
    int8_t y
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  char r = Ring1_Intrinsic_Subtract_X64_subtract_s8(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Subtract_X86_subtract_s8(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_subtract_u16
  (
    uint16_t *result,
    uint16_t x,
    uint16_t y
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  char r = Ring1_Intrinsic_Subtract_X64_subtract_u16(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Subtract_X86_subtract_u16(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_subtract_s16
  (
    int16_t *result,
    int16_t x,
    int16_t y
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  char r = Ring1_Intrinsic_Subtract_X64_subtract_s16(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Subtract_X86_subtract_s16(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_subtract_u32
  (
    uint32_t *result,
    uint32_t x,
    uint32_t y
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  char r = Ring1_Intrinsic_Subtract_X64_subtract_u32(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Subtract_X86_subtract_u32(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_subtract_s32
  (
    int32_t *result,
    int32_t x,
    int32_t y
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  char r = Ring1_Intrinsic_Subtract_X64_subtract_s32(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Subtract_X86_subtract_s32(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_subtract_u64
  (
    uint64_t *result,
    uint64_t x,
    uint64_t y
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  char r = Ring1_Intrinsic_Subtract_X64_subtract_u64(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Subtract_X86_subtract_u64(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_subtract_s64
  (
    int64_t *result,
    int64_t x,
    int64_t y
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  char r = Ring1_Intrinsic_Subtract_X64_subtract_s64(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Subtract_X86_subtract_s64(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_subtract_sz
  (
    size_t *result,
    size_t x,
    size_t y
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  size_t t;
#if defined(_M_X64)
  if (Ring1_Intrinsic_subtract_u64(&t, (uint64_t)x, (uint64_t)y)) {
    *result = t;
    return Ring1_Result_Failure;
  }
#elif defined(_M_IX86)
  if (Ring1_Intrinsic_subtract_u32(&t, (uint32_t)x, (uint32_t)y)) {
    *result = t;
    return Ring1_Result_Failure;
  }
#else
  #error("target architecture not supported")
#endif
  *result = t;
  return Ring1_Result_Success;
}
