// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/getTemporaryDirectory.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Windows/getTemporaryDirectory.h"

#include "Ring1/Memory/_Include.h"
#include "Ring1/Status.h"
#include "Ring1/FileSystem/Path.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Windows_getTemporaryDirectory
  (
    Ring1_FileSystem_Path** result
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  char t;
  DWORD bufferSize = GetTempPath(0, &t);
  if (!bufferSize) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  if (bufferSize > SIZE_MAX - 1) {
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  // bufferSize does not include the zero terminator.
  char* buffer = NULL;
  if (Ring1_Memory_allocate(&buffer, (size_t)(bufferSize) + 1)) {
    return Ring1_Result_Failure;
  }
  if (bufferSize - 1 != GetTempPath(bufferSize + 1, buffer)) {
    Ring1_Memory_deallocate(buffer);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path* path;
  if (Ring1_FileSystem_Path_create(&path, buffer, bufferSize - 1)) {
    Ring1_Memory_deallocate(buffer);
    return Ring1_Result_Failure;
  }
  *result = path;
  return Ring1_Result_Success;
}
