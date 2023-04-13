#if !defined(RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_U16_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_U16_H_INCLUDED

#include <inttypes.h>

#if defined(_M_IX86)

char _fastcall
Ring1_Intrinsic_Multiply_X86_multiply_u16
  (
    uint16_t x,
    uint16_t y,
    uint16_t* z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_U16_H_INCLUDED
