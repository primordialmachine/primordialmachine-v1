#include "Ring1/Intrinsic/Multiply/X86/multiply_u64.h"

#if defined(_M_IX86)

static inline uint64_t
__umul128
  (
    uint64_t multiplier,
    uint64_t multiplicand,
    uint64_t* product_hi
  )
{
  // multiplier   = ab = a * 2^32 + b
  // multiplicand = cd = c * 2^32 + d
  //   ab * cd
  // = (a * 2^32 + b) * (c * 2^32 + d)
  // = a * 2^32 * (c * 2^32 + d) + b * (c * 2^32 + d)
  // = a * 2^32 * c * 2^32 + a * 2^32 * d + b * c * 2^32 + b * d
  // = a * c * 2^64 + (a * d + b * c) * 2^32 + b * d
  uint64_t a = multiplier >> 32;
  uint64_t b = multiplier & 0xFFFFFFFF;
  uint64_t c = multiplicand >> 32;
  uint64_t d = multiplicand & 0xFFFFFFFF;

  // uint64_t ac = a * c;
  uint64_t ad = a * d;
  // uint64_t bc = b * c;
  uint64_t bd = b * d;

  uint64_t adbc = ad + (b * c);
  uint64_t adbc_carry = adbc < ad ? 1 : 0;

  // multiplier * multiplicand = product_hi * 2^64 + product_lo
  uint64_t product_lo = bd + (adbc << 32);
  uint64_t product_lo_carry = product_lo < bd ? 1 : 0;
  *product_hi = (a * c) + (adbc >> 32) + (adbc_carry << 32) + product_lo_carry;

  return product_lo;
}

char
Ring1_Intrinsic_Multiply_X86_multiply_u64
  (
    uint64_t x,
    uint64_t y,
    uint64_t* z
  )
{
  uint64_t lo, hi;
  lo = __umul128(x, y, &hi);
  *z = lo;
  return 0 != hi;
}

#endif
