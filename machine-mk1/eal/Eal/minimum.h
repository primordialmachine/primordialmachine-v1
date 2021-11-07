/// @file Eel/minimum.h
/// @brief Minimum of values.
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_EAL_MINIMUM_H_INCLUDED)
#define MACHINE_EAL_MINIMUM_H_INCLUDED



#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif
#include "Eal/Compiler.h"
#include "Eal/Types.h"



#define IMPLEMENTATION(NAME, TYPE) \
  INLINE TYPE NAME(TYPE const x, TYPE const y) { return x < y ? x : y; }

/// @{
/// @brief Get the minimum of two values.
/// @param x The first value.
/// @param y The second value.
/// @return The minimum of the first and the second value.
IMPLEMENTATION(Machine_Eal_minimum_sz, size_t)

IMPLEMENTATION(Machine_Eal_minimum_u8, uint8_t)

IMPLEMENTATION(Machine_Eal_minimum_u16, uint16_t)

IMPLEMENTATION(Machine_Eal_minimum_u32, uint32_t)

IMPLEMENTATION(Machine_Eal_minimum_u64, uint64_t)
/// @}

#undef IMPLEMENTATION


#endif // MACHINE_EAL_MINIMUM_H_INCLUDED
