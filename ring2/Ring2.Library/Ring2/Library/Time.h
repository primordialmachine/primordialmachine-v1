// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Time.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_TIME_H_INCLUDED)
#define RING2_LIBRARY_TIME_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Time.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring1/Ring1.h"


/// @brief Get the time, in milliseconds, since the start of the system.
/// @return The time, in milliseconds, since the start of the system.
/// @warning This value may wrap around.
Ring1_CheckReturn() uint64_t
Machine_Time_getNowMilliseconds
  (
  );

/// @brief Get the time, in seconds, since the start of the system.
/// @return The time, in seconds, since the start of the system.
/// @warning This value may wrap around.
Ring1_CheckReturn() uint64_t
Machine_Time_getNowSeconds
  (
  );

/// @brief Get the time, in minutes, since the start of the system.
/// @return The time, in minutes, since the start of the system.
/// @warning This value may wrap around.
Ring1_CheckReturn() uint64_t
Machine_Time_getNowMinutes
  (
  );

/// @brief Get the time, in milliseconds, since the start of the system.
/// @return The time, in milliseconds, since the start of the system.
/// @warning This value may be +INFINITY.
/// The current time in milliseconds.
Ring1_CheckReturn() float
Machine_Time_getNowMillisecondsFloat
  (
  );

/// @brief Get the time, in seconds, since the start of the system.
/// @return The time, in seconds, since the start of the system.
/// @warning This value may be +INFINITY.
/// The current time in seconds and fractions of seconds.
Ring1_CheckReturn() float
Machine_Time_getNowSecondsFloat
  (
  );

/// @brief Get the time, in minutes, since the start of the system.
/// @return The time, in minutes, since the start of the system.
/// @warning This value may be +INFINITY.
/// The current time in minutes and fractions of minutes.
Ring1_CheckReturn() float
Machine_Time_getNowMinutesFloat
  (
  );


#endif // RING2_LIBRARY_TIME_H_INCLUDED
