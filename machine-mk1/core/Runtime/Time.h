/// @file Runtime/Time.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_TIME_H_INCLUDED)
#define MACHINE_RUNTIME_TIME_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif


#include "_Eal.h"

/// @brief Get the time, in milliseconds, since the start of the system.
/// @return The time, in milliseconds, since the start of the system.
/// @warning This value may wrap around.
uint64_t Machine_Time_getNowMilliseconds();

/// @brief Get the time, in seconds, since the start of the system.
/// @return The time, in seconds, since the start of the system.
/// @warning This value may wrap around.
uint64_t Machine_Time_getNowSeconds();

/// @brief Get the time, in minutes, since the start of the system.
/// @return The time, in minutes, since the start of the system.
/// @warning This value may wrap around.
uint64_t Machine_Time_getNowMinutes();



/// @brief Get the time, in milliseconds, since the start of the system.
/// @return The time, in milliseconds, since the start of the system.
/// @warning This value may be +INFINITY.
/// The current time in milliseconds.
float Machine_Time_getNowMillisecondsFloat();

/// @brief Get the time, in seconds, since the start of the system.
/// @return The time, in seconds, since the start of the system.
/// @warning This value may be +INFINITY.
/// The current time in seconds and fractions of seconds.
float Machine_Time_getNowSecondsFloat();

/// @brief Get the time, in minutes, since the start of the system.
/// @return The time, in minutes, since the start of the system.
/// @warning This value may be +INFINITY.
/// The current time in minutes and fractions of minutes.
float Machine_Time_getNowMinutesFloat();



#endif // MACHINE_RUNTIME_TIME_H_INCLUDED
