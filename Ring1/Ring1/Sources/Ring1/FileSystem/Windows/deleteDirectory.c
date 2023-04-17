// Copyright (c) 2023 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/deleteDirectory.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Windows/deleteDirectory.h"

#include "Ring1/Memory/_Include.h"
#include "Ring1/Status.h"
#include "Ring1/FileSystem/Path.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Windows_deleteDirectory
  (
    Ring1_FileSystem_Path* path
  )
{
  if (Ring1_Unlikely(!path)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  char* p; size_t n;
  if (Ring1_FileSystem_Path_toString(path, true, &p, &n)) {
    return Ring1_Result_Failure;
  }
  if (!RemoveDirectory(p)) {
    Ring1_Memory_deallocate(p);
    p = NULL;
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  Ring1_Memory_deallocate(p);
  p = NULL;
  return Ring1_Result_Success;
}
