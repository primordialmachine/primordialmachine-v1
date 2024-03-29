// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Time.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Time.h"


#include "Ring1/Status.h"
#include "Ring2/_Include.h"


Ring1_BeginDependencies()
  Ring1_Dependency(Ring1, Time)
  Ring1_Dependency(Ring2, StaticVariablesModule)
Ring1_EndDependencies()

static bool g_initialized = false;

static void onShutdown() {
  shutdownDependencies();
  g_initialized = false;
}

static void
ensureInitialized
  (
  )
{
  if (!g_initialized) {
    if (startupDependencies()) {
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    if (Ring2_registerStaticVariables(&onShutdown)) {
      shutdownDependencies();
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    g_initialized = true;
  }
}

Ring1_CheckReturn() uint64_t
Machine_Time_getNowMilliseconds
  (
  )
{
  ensureInitialized();
  uint64_t temporary;
  if (Ring1_Time_getNowMilliseconds_u64(&temporary)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}

Ring1_CheckReturn() uint64_t
Machine_Time_getNowSeconds
  (
  )
{
  ensureInitialized();
  uint64_t temporary;
  if (Ring1_Time_getNowSeconds_u64(&temporary)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}

Ring1_CheckReturn() uint64_t
Machine_Time_getNowMinutes
  (
  )
{
  ensureInitialized();
  uint64_t temporary;
  if (Ring1_Time_getNowMinutes_u64(&temporary)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}

Ring1_CheckReturn() float
Machine_Time_getNowMillisecondsFloat
  (
  )
{
  ensureInitialized();
  float temporary;
  if (Ring1_Time_getNowMilliseconds_f32(&temporary)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}

Ring1_CheckReturn() float
Machine_Time_getNowSecondsFloat
  (
  )
{
  ensureInitialized();
  float temporary;
  if (Ring1_Time_getNowSeconds_f32(&temporary)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}

Ring1_CheckReturn() float
Machine_Time_getNowMinutesFloat
  (
  )
{
  ensureInitialized();
  float temporary;
  if (Ring1_Time_getNowSeconds_f32(&temporary)) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    Ring2_jump();
  }
  return temporary;
}
