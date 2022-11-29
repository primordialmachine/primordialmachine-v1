// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Conversion/stringToFloat.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Conversion/stringToFloat.h"

#include "Ring1/Conversion/_Buffer.h"
#include "Ring1/Conversion/_Parser.h"
#include "Ring1/Memory.h"
#include "Ring1/Status.h"
#include <string.h>
#include <stdlib.h>

Ring1_CheckReturn() bool
parse
  (
    char const* start,
    char const* end
  )
{
  char const* current = start;

  // ('+'|'-')?
  if (current != end && (*current == '+' || *current == '-')) {
    current++;
  }
  if (current == end) {
    return false;
  }
  if ('.' == *current) {
    // '.' digit+
    current++;
    if (!isDigit(NULL, current, start, end)) {
      return false;
    }
    do {
      current++;
    } while (isDigit(NULL, current, start, end));
  } else if (isDigit(NULL, current, start, end)) {
    // digit+ ('.' digit*)
    do {
      current++;
    } while (isDigit(NULL, current, start, end));
    if (current != end && ('.' == *current)) {
      current++;
    }
    while (isDigit(NULL, current, start, end)) {
      current++;
    }
  } else if ('n' == *current) {
    // 'nan'
    if (!isString(&current, current, start, end, "nan", sizeof("nan") - 1)) {
      Ring1_Status_set(Ring1_Status_ConversionFailed);
      return Ring1_Result_Failure;
    }
  } else if ('i' == *current) {
    // 'inf'
    if (!isString(&current, current, start, end, "inf", sizeof("inf") - 1)) {
      return false;
    }
  } else {
    return false;
  }

  // exponent?
  if (current != end && ('e' == *current || 'E' == *current)) {
    current++;
    // ('+'|'-')?
    if (current != end && ('+' == *current || '-' == *current)) {
      current++;
    }
    if (!isDigit(NULL, current, start, end)) {
      return false;
    }
    do {
      current++;
    } while (isDigit(NULL, current, start, end));
  }

  // end
  if (current != end) {
    return false;
  }

  return true;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Conversion_stringToFloat
  (
    float *result,
    char const* start,
    char const* end
  )
{
  if (Ring1_Unlikely(!start || !end || !result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  if (!parse(start, end)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  // Now perform conversion.
  if (end - start > SIZE_MAX) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }
  char* buffer = NULL;
  if (Ring1_Conversion__Buffer_get(&buffer, end - start + 1)) {
    return Ring1_Result_Failure;
  }
  memcpy(buffer, start, end - start);
  buffer[end - start] = '\0';
  char* current = NULL;
  float v = strtof(start, &current);
  if (current != end) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }
  *result = v;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Conversion_stringToDouble
  (
    double *result,
    char const* start,
    char const* end
  )
{
  if (Ring1_Unlikely(!start || !end || !result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  if (!parse(start, end)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  // Now perform conversion.
  if (end - start > SIZE_MAX) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }
  char* buffer = NULL;
  if (Ring1_Conversion__Buffer_get(&buffer, end - start + 1)) {
    return Ring1_Result_Failure;
  }
  memcpy(buffer, start, end - start);
  buffer[end - start] = '\0';
  char* current = NULL;
  double v = strtod(start, &current);
  if (current != end) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }
  *result = v;
  return Ring1_Result_Success;
}
