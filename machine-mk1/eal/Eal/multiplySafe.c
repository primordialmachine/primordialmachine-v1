/// @file Eel/multiplySafe.c
/// @brief Safe multiplication functions.
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_EAL_PRIVATE (1)
#include "Eal/multiplySafe.h"



#include <intsafe.h>



#define IMPLEMENTATION(NAME, FUNCTION,TYPE) bool NAME(TYPE *z, TYPE x, TYPE y) { \
  TYPE t; \
  HRESULT r = FUNCTION(x, y, &t); \
  if (r != S_OK) { \
    if (z) *z = (TYPE)-1; \
    return false; \
  } else { \
    if (z) *z = t; \
    return true; \
  } \
}

IMPLEMENTATION(Machine_Eal_multiplySafe_sz, SizeTMult, size_t)

IMPLEMENTATION(Machine_Eal_multiplySafe_u8, UInt8Mult, uint8_t)

IMPLEMENTATION(Machine_Eal_multiplySafe_u16, UInt16Mult, uint16_t)

IMPLEMENTATION(Machine_Eal_multiplySafe_u32, UInt32Mult, uint32_t)

IMPLEMENTATION(Machine_Eal_multiplySafe_u64, UInt64Mult, uint64_t)

#undef IMPLEMENTATION
