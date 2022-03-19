/// @file Eel/leastPowerOfTwoGreaterThanOrEqualTo.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_EAL_LEASTPOWEROFTWOGREATERTHANOREQUALTO_H_INCLUDED)
#define MACHINE_EAL_LEASTPOWEROFTWOGREATERTHANOREQUALTO_H_INCLUDED



#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif
#include "Eal/Compiler.h"
#include "Eal/Types.h"



/// @{
/// @brief Compute the least power of two greater than or equal to a given value.
/// @param y A pointer to a variable.
/// @param x The value.
/// @return @a true if the power of two exists, @a false otherwise.
/// @remark
/// The algorithm first checks if @a x is 0.
/// In that case *z is assigned 1 and true is returned.
/// Otherwise it checks if @a x is a power of two.
/// In that case *z is assigned x and true is returned.
/// Otherwise
/// it sets i = 0.
/// As long as x is greater than 0 it divides x by 2 and increments i.
/// If i is equal to the number of bits of the type, then *z is assigned (TYPE)-1 and false is returned.
/// Otherwise *z is assigned 2^i and true is returned.
/// @remark
/// Example:
/// Assume x = 0 is passed.
/// As x is 0 the first branch is taken.
/// Consequently, the return value is true and *z is 1.
/// 
/// @remark
/// Example:
/// Assume x = 31 is passed. 
/// As x = 31 is not 0 the first branch is not taken.
/// As x = 31 is no power of two, Machine_isPowerOfTwo_sz(31) evaluates to false and the second branch is not taken.
/// Hence the third branch is taken.
/// 
/// Before the first execution of the loop x = 31 and i = 0.
/// The following table represents x and i at the end of each iteration of the loop.
/// --------------------
/// Iteration | x  | i |
/// --------------------
/// 1         | 15 | 1 |
/// --------------------
/// 2         | 7  | 2 |
/// --------------------
/// 3         | 3  | 3 |
/// --------------------
/// 4         | 1  | 4 |
/// --------------------
/// 5         | 0  | 5 |
/// --------------------
/// Consequently, the return value is true and *z is 1 << 5 ~ 2^5 ~ 32 which is the least power of two greater than or equal to 31.
bool Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_sz(size_t* z, size_t x);

bool Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_u8(uint8_t* z, uint8_t x);

bool Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_u16(uint16_t* z, uint16_t x);

bool Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_u32(uint32_t* z, uint32_t x);

bool Machine_Eal_leastPowerOfTwoGreaterThanOrEqualTo_u64(uint64_t* z, uint64_t x);

/// @}



#endif // MACHINE_EAL_LEASTPOWEROFTWOGREATERTHANOREQUALTO_H_INCLUDED
