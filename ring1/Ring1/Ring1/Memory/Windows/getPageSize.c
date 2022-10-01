// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Memory/Windows/getPageSize.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Memory/Windows/getPageSize.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "Ring1/Status.h"

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_Windows_getPageSize
  (
    size_t* result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  SYSTEM_INFO i;
  GetNativeSystemInfo(&i);
  *result = i.dwPageSize;
  return Ring1_Result_Success;
}
