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

#include "Ring1/Memory.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_getFileContents
  (
    char const* pathname,
    Ring1_FileSystem_AllocateCallback* allocate,
    Ring1_FileSystem_DeallocateCallback* deallocate,
    char** bytes,
    size_t* numberOfBytes
  )
{ 
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Linux_getFileContents(pathname, allocate, deallocate, bytes, numberOfBytes);
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Windows_getFileContents(pathname, allocate, deallocate, bytes, numberOfBytes);
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI")
#endif
}
