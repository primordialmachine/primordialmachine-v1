// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/countDecimalDigits.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_COUNTDECIMALDIGITS_H_INCLUDED)
#define RING1_INTRINSIC_COUNTDECIMALDIGITS_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include <inttypes.h>

/// @brief Determine the least number of digits required to represent the specified value in base-10 represention.
/// @param value The value.
/// @return The number of digits.
/// @remarks
/// The number of digits for the value 0 is, 1,
/// the number of digits for the values 1 to 9 is 1,
/// the number of digits for th values 10 to 19 is 2,
/// etc.
Ring1_NoDiscardReturn() uint8_t
Ring1_countDecimalDigits_u8
  (
    uint8_t value
  );
  
/// @brief Determine the least number of digits required to represent the specified value in base-10 represention.
/// @param value The value.
/// @return The number of digits.
/// @remarks
/// The number of digits for the value 0 is, 1,
/// the number of digits for the values 1 to 9 is 1,
/// the number of digits for th values 10 to 19 is 2,
/// etc.
Ring1_NoDiscardReturn() uint8_t
Ring1_countDecimalDigits_u16
  (
    uint16_t value
  );
  
/// @brief Determine the least number of digits required to represent the specified value in base-10 represention.
/// @param value The value.
/// @return The number of digits.
/// @remarks
/// The number of digits for the value 0 is, 1,
/// the number of digits for the values 1 to 9 is 1,
/// the number of digits for th values 10 to 19 is 2,
/// etc.
Ring1_NoDiscardReturn() uint8_t
Ring1_countDecimalDigits_u32
  (
    uint32_t value
  );

/// @brief Determine the least number of digits required to represent the specified value in base-10 represention.
/// @param value The value.
/// @return The number of digits.
/// @remarks
/// The number of digits for the value 0 is, 1,
/// the number of digits for the values 1 to 9 is 1,
/// the number of digits for th values 10 to 19 is 2,
/// etc.
Ring1_NoDiscardReturn() uint8_t
Ring1_countDecimalDigits_u64
  (
    uint64_t value
  );

#endif // RING1_INTRINSIC_COUNTDECIMALDIGITS_H_INCLUDED
