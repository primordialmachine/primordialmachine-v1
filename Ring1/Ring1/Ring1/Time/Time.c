/// @file Ring1/Time/Time.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Ring1/Time/Time.h"

#include "Ring1/Status.h"

static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_Module_Define(Ring1, Time, initializeModule, uninitializeModule)

static Ring1_Result
initializeModule
  (
  )
{ return Ring1_Result_Success; } 

static void
uninitializeModule
  (
  )
{/*Intentionally empty.*/}

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowMilliseconds_u64
  (
    uint64_t *result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = (uint64_t)GetTickCount64();
  return Ring1_Result_Success;
}

#else

  #error("Platform not (yet) supported.")

#endif

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowSeconds_u64
  (
    uint64_t *result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  uint64_t temporary;
  if (Ring1_Time_getNowMilliseconds_u64(&temporary)) {
    return Ring1_Result_Failure;
  }
  *result = temporary / UINT64_C(1000);
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowMinutes_u64
  (
    uint64_t *result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  uint64_t temporary;
  if (Ring1_Time_getNowMilliseconds_u64(&temporary)) {
    return Ring1_Result_Failure;
  }
  *result = temporary / UINT64_C(1000 * 60);
  return Ring1_Result_Success;
}


#include <float.h>

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowMilliseconds_f32
  (
    float *result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  uint64_t temporary;
  if (Ring1_Time_getNowMilliseconds_u64(&temporary)) {
    return Ring1_Result_Failure;
  }
  if (temporary > FLT_MAX) {
    *result = FLT_MAX;
  } else {
    *result = (float)temporary;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowSeconds_f32
  (
    float* result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  float temporary;
  if (Ring1_Time_getNowMilliseconds_f32(&temporary)) {
    return Ring1_Result_Failure;
  }
  *result = temporary / (1000.f);
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowMinutes_f32
  (
    float *result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  float temporary;
  if (Ring1_Time_getNowMilliseconds_f32(&temporary)) {
    return Ring1_Result_Failure;
  }
  *result = temporary / (1000.f * 60.f);
  return Ring1_Result_Success;
}
