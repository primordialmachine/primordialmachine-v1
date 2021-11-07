/// @file Eel/isPowerOfTwo.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_EAL_ISPOWEROFTWO_H_INCLUDED)
#define MACHINE_EAL_ISPOWEROFTWO_H_INCLUDED



#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif
#include "Eal/Compiler.h"
#include "Eal/Types.h"



/// @brief Get if a value is a power of two.
/// @param x The value.
/// @return @a true if @a x is a power of two, @a false otherwise.
/// @remark In particular, this function correctly returns @a false if @a x is @a 0.
bool Machine_Eal_isPowerOfTwo_sz(size_t x);

/// @brief Get if a value is a power of two.
/// @param x The value.
/// @return @a true if @a x is a power of two, @a false otherwise.
/// @remark In particular, this function correctly returns @a false if @a x is @a 0.
bool Machine_Eal_isPowerOfTwo_u64(uint64_t x);

/// @brief Get if a value is a power of two.
/// @param x The value.
/// @return @a true if @a x is a power of two, @a false otherwise.
/// @remark In particular, this function correctly returns @a false if @a x is @a 0.
bool Machine_Eal_isPowerOfTwo_u32(uint32_t x);

/// @brief Get if a value is a power of two.
/// @param x The value.
/// @return @a true if @a x is a power of two, @a false otherwise.
/// @remark In particular, this function correctly returns @a false if @a x is @a 0.
bool Machine_Eal_isPowerOfTwo_u16(uint16_t x);

/// @brief Get if a value is a power of two.
/// @param x The value.
/// @return @a true if @a x is a power of two, @a false otherwise.
/// @remark In particular, this function correctly returns @a false if @a x is @a 0.
bool Machine_Eal_isPowerOfTwo_u8(uint8_t x);



#endif // MACHINE_EAL_ISPOWEROFTWO_H_INCLUDED
