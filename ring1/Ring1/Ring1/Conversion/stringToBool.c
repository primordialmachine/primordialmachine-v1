// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Conversion/stringToBool.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Conversion/stringToBool.h"

#include "Ring1/Conversion/_Buffer.h"
#include "Ring1/Conversion/_Parser.h"
#include "Ring1/Memory.h"
#include "Ring1/Status.h"
#include <string.h>
#include <stdlib.h>

Ring1_CheckReturn() Ring1_Result
Ring1_Conversion_stringToBool
  (
    bool *result,
    char const* start,
    char const* end
  )
{
  if (Ring1_Unlikely(!result || !start || !end)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  int temporary;
  Ring1_Memory_compare(&temporary, start, end - start, "true", sizeof("true") - 1, Ring1_Memory_Compare_Lexicographic);
  if (!temporary) {
    *result = true;
    return Ring1_Result_Success;
  }
  Ring1_Memory_compare(&temporary, start, end - start, "false", sizeof("false") - 1, Ring1_Memory_Compare_Lexicographic);
  if (!temporary) {
    *result = false;
    return Ring1_Result_Success;
  }
  Ring1_Status_set(Ring1_Status_ConversionFailed);
  return Ring1_Result_Failure;
}
