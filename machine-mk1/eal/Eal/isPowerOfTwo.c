/// @file Eal/isPowerOfTwo.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_EAL_PRIVATE (1)
#include "Eal/isPowerOfTwo.h"



#define IMPLEMENTATION(TYPE) (TYPE x) { \
  return x != 0 && ((x & (x - 1)) == 0); \
}

bool Machine_Eal_isPowerOfTwo_sz
IMPLEMENTATION(size_t)

bool Machine_Eal_isPowerOfTwo_u64
IMPLEMENTATION(uint64_t)

bool Machine_Eal_isPowerOfTwo_u32
IMPLEMENTATION(uint32_t)

bool Machine_Eal_isPowerOfTwo_u16
IMPLEMENTATION(uint16_t)

bool Machine_Eal_isPowerOfTwo_u8
IMPLEMENTATION(uint8_t)

#undef IMPLEMENTATION
