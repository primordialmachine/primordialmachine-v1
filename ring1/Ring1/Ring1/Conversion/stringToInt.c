// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Conversion/stringToInt.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Conversion/stringToInt.h"

#include "Ring1/Conversion/_Parser.h"
#include "Ring1/Intrinsic/Unlikely.h"
#include "Ring1/Status.h"

#define MAXDIV10 (INT64_MAX / 10)

#define MAXMOD10 (INT64_MAX % 10)

Ring1_Intrinsic_CheckReturn() Ring1_Result
Ring1_Conversion_stringToInt64
  (
    int64_t* result,
    char const* start,
    char const* end
  )
{
  if (Ring1_Intrinsic_Unlikely(!result || !start || !end)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  char const* current = start;
  
  // No symbols? Fail.
  if (current == end) { 
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }
  
  // ('+'|'-')?
  bool negative = false;
  if (*current == '+' || *current == '-') {
    negative = (*current == '-');
    current++;
  }
  
  int64_t value = 0;
  
  // digit+
  if (!isDigit(NULL, current, start, end)) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }
  do {
    uint8_t digit = *current - '0';
    if (value >= MAXDIV10 && (value > MAXDIV10 || digit > MAXMOD10 + (negative ? 1 : 0))) {
      Ring1_Status_set(Ring1_Status_ConversionFailed);
      return Ring1_Result_Failure;
    }
    value *= 10;
    value += digit;
    current++;
  } while (isDigit(NULL, current, start, end));

  // end
  if (current != end) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }

  if (negative)
    value = -value;

  *result = value;
  return Ring1_Result_Success;
}

Ring1_Intrinsic_CheckReturn() Ring1_Result
Ring1_Conversion_stringToInt32
  (
    int32_t *result,
    char const* start,
    char const* end
  )
{
  int64_t temporary;
  if (Ring1_Conversion_stringToInt64(&temporary, start, end)){
    return Ring1_Result_Failure;
  }
  if (temporary < INT32_MIN || temporary > INT32_MAX) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;    
  }
  *result = (int32_t)temporary;
  return Ring1_Result_Success;
}

Ring1_Intrinsic_CheckReturn() Ring1_Result
Ring1_Conversion_stringToInt16
  (
    int16_t *result,
    char const* start,
    char const* end
  )
{
  int64_t temporary;
  if (Ring1_Conversion_stringToInt64(&temporary, start, end)){
    return Ring1_Result_Failure;
  }
  if (temporary < INT16_MIN || temporary > INT16_MAX) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;    
  }
  *result = (int16_t)temporary;
  return Ring1_Result_Success;
}

Ring1_Intrinsic_CheckReturn() Ring1_Result
Ring1_Conversion_stringToInt8
  (
    int8_t *result,
    char const* start,
    char const* end
  )
{
  int64_t temporary;
  if (Ring1_Conversion_stringToInt64(&temporary, start, end)){
    return Ring1_Result_Failure;
  }
  if (temporary < INT8_MIN || temporary > INT8_MAX) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;    
  }
  *result = (int8_t)temporary;
  return Ring1_Result_Success;
}
