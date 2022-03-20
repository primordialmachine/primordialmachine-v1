#if !defined(RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_S32_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_S32_H_INCLUDED

#include <inttypes.h>

#if defined(_M_IX86)

char _fastcall
Ring1_Intrinsic_Multiply_X86_multiply_s32
  (
    int32_t x,
    int32_t y,
    int32_t *z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_S32_H_INCLUDED
