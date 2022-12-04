// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/setFileContents.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/setFileContents.h"

#include "Ring1/FileSystem/Configuration.h"
#include <stdio.h>

#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Linux/setFileContents.h"
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Windows/setFileContents.h"
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUNX, RING1_FILESYSTEM_CONFIGURATION_BACKEND_OSX, or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS")
#endif

#include "Ring1/Memory.h"

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_setFileContents
  (
    char const* pathname,
    void const* bytes,
    size_t numberOfBytes
  )
{
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Linux_setFileContents(pathname, bytes, numberOfBytes);
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Windows_setFileContents(pathname, bytes, numberOfBytes);
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUNX, RING1_FILESYSTEM_CONFIGURATION_BACKEND_OSX, or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS")
#endif
}
