// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Conversion/stringToUint.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Conversion/stringToUint.h"

#include "Ring1/Conversion/_Parser.h"
#include "Ring1/Status.h"

#define MAXDIV10 (INT64_MAX / 10)

#define MAXMOD10 (INT64_MAX % 10)

Ring1_CheckReturn() Ring1_Result
Ring1_Conversion_stringToUint64
  (
    uint64_t *result,
    char const* start,
    char const* end
  )
{
  if (Ring1_Unlikely(!result || !start || !end)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  char const* current = start;
  
  // No symbols? Fail.
  if (current == end) { 
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }
  
  // ('+')?
  if (*current == '+') {
    current++;
  }
  
  uint64_t value = 0;
  
  // digit+
  if (!isDigit(NULL, current, start, end)) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }
  do {
    uint8_t digit = *current - '0';
    if (value >= MAXDIV10 && (value > MAXDIV10 || digit > MAXMOD10)) {
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

  *result = value;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Conversion_stringToUint32
  (
    uint32_t* result,
    char const* start,
    char const* end
  )
{
  uint64_t temporary;
  if (Ring1_Conversion_stringToUint64(&temporary, start, end)) {
    return Ring1_Result_Failure;
  }
  if (temporary > UINT32_MAX) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;    
  }
  *result = (uint32_t)temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Conversion_stringToUint16
  (
    uint16_t* result,
    char const* start,
    char const* end
  )
{
  uint64_t temporary;
  if (Ring1_Conversion_stringToUint64(&temporary, start, end)){
    return Ring1_Result_Failure;
  }
  if (temporary > UINT16_MAX) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;    
  }
  *result = (uint16_t)temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Conversion_stringToUint8
  (
    uint8_t* result,
    char const* start,
    char const* end
  )
{
  uint64_t temporary;
  if (Ring1_Conversion_stringToUint64(&temporary, start, end)) {
    return Ring1_Result_Failure;
  }
  if (temporary > UINT8_MAX) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;    
  }
  *result = (uint8_t)temporary;
  return Ring1_Result_Success;
}
