#include "Ring1/Intrinsic/Multiply/multiply.h"

#include "Ring1/Status.h"

#if defined(_M_X64)
  #include "Ring1/Intrinsic/Multiply/X64/multiply_u8.h"
  #include "Ring1/Intrinsic/Multiply/X64/multiply_s8.h"
  #include "Ring1/Intrinsic/Multiply/X64/multiply_u16.h"
  #include "Ring1/Intrinsic/Multiply/X64/multiply_s16.h"
  #include "Ring1/Intrinsic/Multiply/X64/multiply_u32.h"
  #include "Ring1/Intrinsic/Multiply/X64/multiply_s32.h"
  #include "Ring1/Intrinsic/Multiply/X64/multiply_u64.h"
  #include "Ring1/Intrinsic/Multiply/X64/multiply_s64.h"
#elif defined(_M_IX86)
  #include "Ring1/Intrinsic/Multiply/X86/multiply_u8.h"
  #include "Ring1/Intrinsic/Multiply/X86/multiply_s8.h"
  #include "Ring1/Intrinsic/Multiply/X86/multiply_u16.h"
  #include "Ring1/Intrinsic/Multiply/X86/multiply_s16.h"
  #include "Ring1/Intrinsic/Multiply/X86/multiply_u32.h"
  #include "Ring1/Intrinsic/Multiply/X86/multiply_s32.h"
  #include "Ring1/Intrinsic/Multiply/X86/multiply_u64.h"
  #include "Ring1/Intrinsic/Multiply/X86/multiply_s64.h"
#else
  #error("target architecture not supported")
#endif

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_multiply_u8
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
  char r = Ring1_Intrinsic_Multiply_X64_multiply_u8(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Multiply_X86_multiply_u8(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_multiply_s8
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
  char r = Ring1_Intrinsic_Multiply_X64_multiply_s8(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Multiply_X86_multiply_s8(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_multiply_u16
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
  char r = Ring1_Intrinsic_Multiply_X64_multiply_u16(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Multiply_X86_multiply_u16(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_multiply_s16
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
  char r = Ring1_Intrinsic_Multiply_X64_multiply_s16(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Multiply_X86_multiply_s16(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_multiply_u32
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
  char r = Ring1_Intrinsic_Multiply_X64_multiply_u32(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Multiply_X86_multiply_u32(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_multiply_s32
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
  char r = Ring1_Intrinsic_Multiply_X64_multiply_s32(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Multiply_X86_multiply_s32(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_multiply_u64
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
  char r = Ring1_Intrinsic_Multiply_X64_multiply_u64(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Multiply_X86_multiply_u64(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_multiply_s64
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
  char r = Ring1_Intrinsic_Multiply_X64_multiply_s64(x, y, result);
#elif defined(_M_IX86)
  char r = Ring1_Intrinsic_Multiply_X86_multiply_s64(x, y, result);
#else
  #error("target architecture not supported")
#endif
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_multiply_sz
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
#if defined(_M_X64)
  uint64_t t;
  char r = Ring1_Intrinsic_Multiply_X64_multiply_u64((size_t)x, (size_t)y, &t);
#elif defined(_M_IX86)
  uint32_t t;
  char r = Ring1_Intrinsic_Multiply_X86_multiply_u32((size_t)x, (size_t)y, &t);
#else
  #error("target architecture not supported")
#endif
  *result = t;
  if (r == 1) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
