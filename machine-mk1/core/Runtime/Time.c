/// @file Runtime/Time.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Time.h"

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

uint64_t Machine_Time_getNowMilliseconds() {
  return (uint64_t)GetTickCount64();
}

uint64_t Machine_Time_getNowSeconds() {
  return Machine_Time_getNowMilliseconds() / UINT64_C(1000);
}

uint64_t Machine_Time_getNowMinutes() {
  return Machine_Time_getNowMilliseconds() / UINT64_C(1000 * 60);
}

#else

  #error("Platform not (yet) supported.")

#endif

#include <float.h>

float Machine_Time_getNowMillisecondsFloat() {
  uint64_t v = Machine_Time_getNowMilliseconds();
  if (v > FLT_MAX) {
    return FLT_MAX;
  }
  return (float)v;
}

float Machine_Time_getNowSecondsFloat() {
  return (Machine_Time_getNowMillisecondsFloat() / (1000.0f));
}

float Machine_Time_getNowMinutesFloat() {
  return (Machine_Time_getNowMillisecondsFloat() / (1000.0f * 60.f));
}
