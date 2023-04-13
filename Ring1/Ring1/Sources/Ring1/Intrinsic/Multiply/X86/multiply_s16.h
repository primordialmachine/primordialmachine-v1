#if !defined(RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_S16_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_S16_H_INCLUDED

#include <inttypes.h>

#if defined(_M_IX86)

char _fastcall
Ring1_Intrinsic_Multiply_X86_multiply_s16
  (
    int16_t x,
    int16_t y,
    int16_t *z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_S16_H_INCLUDED
