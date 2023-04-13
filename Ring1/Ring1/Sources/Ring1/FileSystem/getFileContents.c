// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/getFileContents.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/getFileContents.h"

#include "Ring1/FileSystem/Configuration.h"
#include <stdio.h>

#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Linux/getFileContents.h"
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Windows/getFileContents.h"
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUNX, RING1_FILESYSTEM_CONFIGURATION_BACKEND_OSX, or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS")
#endif

#include "Ring1/Memory/_Include.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_getFileContents
  (
    Ring1_FileSystem_Path* path,
    Ring1_FileSystem_AllocateCallback* allocate,
    Ring1_FileSystem_DeallocateCallback* deallocate,
    char** bytes,
    size_t* numberOfBytes
  )
{
  char* p; size_t n;
  if (Ring1_FileSystem_Path_toString(path, true, &p, &n)) {
    return Ring1_Result_Failure;
  }
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  if (Ring1_FileSystem_Linux_getFileContents(p, allocate, deallocate, bytes, numberOfBytes)) {
    Ring1_Memory_deallocate(p);
    p = NULL;
    return Ring1_Result_Failure;
  }
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  if (Ring1_FileSystem_Windows_getFileContents(p, allocate, deallocate, bytes, numberOfBytes)) {
    Ring1_Memory_deallocate(p);
    p = NULL;
    return Ring1_Result_Failure;
  }
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI")
#endif
  Ring1_Memory_deallocate(p);
  p = NULL;
  return Ring1_Result_Success;
}
