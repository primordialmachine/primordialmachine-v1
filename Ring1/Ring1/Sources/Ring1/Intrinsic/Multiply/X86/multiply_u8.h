#if !defined(RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_U8_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_U8_H_INCLUDED

#include <inttypes.h>

#if defined(_M_IX86)

char _fastcall
Ring1_Intrinsic_Multiply_X86_multiply_u8
  (
    uint8_t x,
    uint8_t y,
    uint8_t *z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_U8_H_INCLUDED
