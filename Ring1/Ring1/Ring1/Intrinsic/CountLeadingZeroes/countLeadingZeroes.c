#include "Ring1/Intrinsic/CountLeadingZeroes/countLeadingZeroes.h"

#if defined(_M_X64)
  #include "Ring1/Intrinsic/CountLeadingZeroes/X64/countLeadingZeroes_u8.h"
  #include "Ring1/Intrinsic/CountLeadingZeroes/X64/countLeadingZeroes_u16.h"
  #include "Ring1/Intrinsic/CountLeadingZeroes/X64/countLeadingZeroes_u32.h"
  #include "Ring1/Intrinsic/CountLeadingZeroes/X64/countLeadingZeroes_u64.h"
#elif defined(_M_IX86)
  #include "Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u8.h"
  #include "Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u16.h"
  #include "Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u32.h"
  #include "Ring1/Intrinsic/CountLeadingZeroes/X86/countLeadingZeroes_u64.h"
#else
  #error("target architecture not supported")
#endif

#include "Ring1/Result.h"
#include "Ring1/Status.h"

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_countLeadingZeroes_u8
  (
    short* result,
    uint8_t x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  *result = Ring1_Intrinsic_CountLeadingZeroes_X64_countLeadingZeroes_u8(x);
#elif defined(_M_IX86)
  *result = Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u8(x);
#else
  #error("target architecture not supported")
#endif
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_countLeadingZeroes_u16
  (
    short* result,
    uint16_t x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  *result = Ring1_Intrinsic_CountLeadingZeroes_X64_countLeadingZeroes_u16(x);
#elif defined(_M_IX86)
  *result = Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u16(x);
#else
  #error("target architecture not supported")
#endif
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_countLeadingZeroes_u32
  (
    short *result,
    uint32_t x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  *result = Ring1_Intrinsic_CountLeadingZeroes_X64_countLeadingZeroes_u32(x);
#elif defined(_M_IX86)
  *result = Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u32(x);
#else
  #error("target architecture not supported")
#endif
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_countLeadingZeroes_u64
  (
    short *result,
    uint64_t x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_M_X64)
  *result = Ring1_Intrinsic_CountLeadingZeroes_X64_countLeadingZeroes_u64(x);
#elif defined(_M_IX86)
  *result = Ring1_Intrinsic_CountLeadingZeroes_X86_countLeadingZeroes_u64(x);
#else
  #error("target architecture not supported")
#endif
  return Ring1_Result_Success;
}
