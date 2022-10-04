// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Intrinsic/atomicCompareExchange.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_INTRINSIC_ATOMICCOMPAREEXCHANGE_H_INCLUDED)
#define MKX_INTRINSIC_ATOMICCOMPAREEXCHANGE_H_INCLUDED


#if defined(_MSC_VER)
#include <stdint.h>
#endif // _MSC_VER


#if defined(_MSC_VER)
/// @brief
/// This function atomically performs
/// @code
/// if (*variable == oldValue)
/// { *variable = newValue; return true; }
/// else
/// { return false; }
/// @endcode
/// @param variable A pointer to the variable.
/// @param oldValue The value to compare the variable value with.
/// @param newValue The value to assign to the variable.
/// @return @a true if the new value was assigned, @a false otherwise.
int8_t
Mkx_Intrinsic_atomicCompareExchange_s8
  (
    volatile int8_t* variable,
    int8_t oldValue,
    int8_t newValue
  );
#endif // _MSC_VER


#if defined(_MSC_VER)
/// @brief
/// This function atomically performs
/// @code
/// if (*variable == oldValue)
/// { *variable = newValue; return true; }
/// else
/// { return false; }
/// @endcode
/// @param variable A pointer to the variable.
/// @param oldValue The value to compare the variable value with.
/// @param newValue The value to assign to the variable.
/// @return @a true if the new value was assigned, @a false otherwise.
int16_t
Mkx_Intrinsic_atomicCompareExchange_s16
  (
    volatile int16_t* variable,
    int16_t oldValue,
    int16_t newValue
  );
#endif // _MSC_VER


#if defined(_MSC_VER)
/// @brief
/// This function atomically performs
/// @code
/// if (*variable == oldValue)
/// { *variable = newValue; return true; }
/// else
/// { return false; }
/// @endcode
/// @param variable A pointer to the variable.
/// @param oldValue The value to compare the variable value with.
/// @param newValue The value to assign to the variable.
/// @return @a true if the new value was assigned, @a false otherwise.
/// @warning
/// The variables must be aligned on a 32 bit boundary.
int32_t
Mkx_Intrinsic_atomicCompareExchange_s32
  (
    volatile int32_t *variable,
    int32_t oldValue,
    int32_t newValue
  );
#endif // _MSC_VER


#endif  // MKX_INTRINSIC_ATOMICCOMPAREEXCHANGE_H_INCLUDED
