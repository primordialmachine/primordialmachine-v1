/// @file Eel/adSafe.h
/// @brief Safe addition functions.
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_EAL_ADDSAFE_H_INCLUDED)
#define MACHINE_EAL_ADDSAFE_H_INCLUDED



#if !defined(MACHINE_EAL_PRIVATE)
#error("Do not include this file directly, include `_Eal.h` instead.")
#endif
#include "Eal/Types.h"



/// @brief Safe addition.
/// @param z A pointer to a variable or a null pointer.
/// @param x The augend.
/// @param y The addend.
/// @return @a true if the sum <code>x+y</code> does not overflow, @a false otherwise.
/// @post
/// If @a z is not null:
/// - If the sum of @a x and @a y does not overflow, <code>*z</code> is assigned the value of the sum.
/// - Otherwise <code>*z</code> is assigned <code>(size_t)-1</code> otherwise.
bool Machine_Eal_addSafe_sz(size_t* z, size_t x, size_t y);

/// @brief Safe addition.
/// @param z A pointer to a variable or a null pointer.
/// @param x The augend.
/// @param y The addend.
/// @return @a true if the sum <code>x+y</code> does not overflow, @a false otherwise.
/// @post
/// If @a z is not null:
/// - If the sum of @a x and @a y does not overflow, <code>*z</code> is assigned the value of the sum.
/// - Otherwise <code>*z</code> is assigned <code>(uint8_t)-1</code>.
bool Machine_Eal_addSafe_u8(uint8_t* z, uint8_t x, uint8_t k);

/// @brief Safe addition.
/// @param z A pointer to a variable or a null pointer.
/// @param x The augend.
/// @param y The addend.
/// @return @a true if the sum <code>x+y</code> does not overflow, @a false otherwise.
/// @post
/// If @a z is not null:
/// - If the sum of @a x and @a y does not overflow, <code>*z</code> is assigned the value of the sum.
/// - Otherwise <code>*z</code> is assigned <code>(uint16_t)-1</code> otherwise.
bool Machine_Eal_addSafe_u16(uint16_t* z, uint16_t x, uint16_t y);

/// @brief Safe addition.
/// @param z A pointer to a variable or a null pointer.
/// @param x The augend.
/// @param y The addend.
/// @return @a true if the sum <code>x+y</code> does not overflow, @a false otherwise.
/// @post
/// If @a z is not null:
/// - If the sum of @a x and @a y does not overflow, <code>*z</code> is assigned the value of the sum.
/// - Otherwise <code>*z</code> is assigned <code>(uint32_t)-1</code> otherwise.
bool Machine_Eal_addSafe_u32(uint32_t* z, uint32_t x, uint32_t y);

/// @brief Safe addition.
/// @param z A pointer to a variable or a null pointer.
/// @param x The multiplicant.
/// @param y The multiplier.
/// @return @a true if the sum <code>x+y</code> does not overflow, @a false otherwise.
/// @post
/// If @a z is not null:
/// - If the sum of @a x and @a y does not overflow, <code>*z</code> is assigned the value of the sum.
/// - Otherwise <code>*z</code> is assigned <code>(uint64_t)-1</code> otherwise.
bool Machine_Eal_addSafe_u64(uint64_t* z, uint64_t x, uint64_t y);



#endif // MACHINE_EAL_ADDSAFE_H_INCLUDED