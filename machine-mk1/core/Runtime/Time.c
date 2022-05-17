/// @file Runtime/Time.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Time.h"

#include "Ring1/Time.h"
#include "Runtime/Status.h"
#include "Ring2/JumpTargetModule.h"

uint64_t Machine_Time_getNowMilliseconds() {
  uint64_t temporary;
  if (Ring1_Time_getNowMilliseconds_u64(&temporary)) {
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}

uint64_t Machine_Time_getNowSeconds() {
  uint64_t temporary;
  if (Ring1_Time_getNowSeconds_u64(&temporary)) {
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}

uint64_t Machine_Time_getNowMinutes() {
  uint64_t temporary;
  if (Ring1_Time_getNowMinutes_u64(&temporary)) {
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}

float Machine_Time_getNowMillisecondsFloat() {
  float temporary;
  if (Ring1_Time_getNowMilliseconds_f32(&temporary)) {
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}

float Machine_Time_getNowSecondsFloat() {
  float temporary;
  if (Ring1_Time_getNowSeconds_f32(&temporary)) {
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}

float Machine_Time_getNowMinutesFloat() {
  float temporary;
  if (Ring1_Time_getNowSeconds_f32(&temporary)) {
    Machine_setStatus(Machine_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}
