/// @file Ring1/Time/Time.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING1_TIME_TIME_H_INCLUDED)
#define RING1_TIME_TIME_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Module.h"
#include "Ring1/Result.h"

Ring1_Module_Declare(Ring1, Time)

// https://primordialmachine.com/api/ring1-library/time-library/Ring1_Time_getNowMilliseconds
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowMilliseconds_u64
  (
    uint64_t* result
  );

// https://primordialmachine.com/api/ring1-library/time-library/Ring1_Time_getNowSeconds
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowSeconds_u64
  (
    uint64_t* result
  );

// https://primordialmachine.com/api/ring1-library/time-library/Ring1_Time_getNowMinutes
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowMinutes_u64
  (
    uint64_t* result
  );

// https://primordialmachine.com/api/ring1-library/time-library/Ring1_Time_getNowMilliseconds
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowMilliseconds_f32
  (
    float* result
  );

// https://primordialmachine.com/api/ring1-library/time-library/Ring1_Time_getNowSeconds
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowSeconds_f32
  (
    float* result
  );

// https://primordialmachine.com/api/ring1-library/time-library/Ring1_Time_getNowMinutes
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Time_getNowMinutes_f32
  (
    float* result
  );

#endif // RING1_TIME_TIME_H_INCLUDED
