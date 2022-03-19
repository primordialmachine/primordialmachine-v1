/// @file Eel/leastPowerOfTwoGreaterThanOrEqualTo.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_EAL_PRIVATE (1)
#include "Eal/leastPowerOfTwoGreaterThanOrEqualTo.h"



#include "Eal/isPowerOfTwo.h"



#define IMPLEMENTATION(TYPE_SUFFIX, TYPE_NAME, BITS) \
  if (x == 0) { \
    if (z) *z = 1; \
    return 1; \
  } else if (Machine_Eal_isPowerOfTwo_##TYPE_SUFFIX(x)) { \
    if (z) *z = x; \
    return true; \
  } else { \
    TYPE_NAME i = 0; \
    while (x) { \
      x >>= 1; \
      i++; \
    } \
    if (i == BITS) { \
      if (z) *z = (TYPE_NAME)-1; \
      return false; \
    } else { \
      if (z) *z = ((TYPE_NAME)1) << i; \
      return true; \
    } \
  }

bool Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_sz(size_t* z, size_t x) {
  IMPLEMENTATION(sz, size_t, SIZE_BITS)
}

bool Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_u8(uint8_t* z, uint8_t x) {
  IMPLEMENTATION(u8, uint8_t, UINT8_BITS)
}

bool Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_u16(uint16_t* z, uint16_t x) {
  IMPLEMENTATION(u16, uint16_t, UINT16_BITS)
}

bool Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_u32(uint32_t* z, uint32_t x) {
  IMPLEMENTATION(u32, uint32_t, UINT32_BITS)
}

bool Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_u64(uint64_t* z, uint64_t x) {
  IMPLEMENTATION(u64, uint64_t, UINT64_BITS)
}

#undef IMPLEMENTATION
