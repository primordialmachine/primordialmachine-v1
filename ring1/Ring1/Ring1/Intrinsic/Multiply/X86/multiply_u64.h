#if !defined(RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_U64_H_INCLUDED)
#define RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_U64_H_INCLUDED

#include <inttypes.h>

#if defined(_M_IX86)

char
Ring1_Intrinsic_Multiply_X86_multiply_u64
  (
    uint64_t x,
    uint64_t y,
    uint64_t* z
  );

#endif

#endif // RING1_INTRINSIC_MULTIPLY_X86_MULTIPLY_U64_H_INCLUDED
