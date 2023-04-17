// Copyright (c) 2023 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/getTemporaryDirectory.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/getTemporaryDirectory.h"

#include "Ring1/FileSystem/Configuration.h"
#include <stdio.h>

#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Linux/getTemporaryDirectory.h"
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Windows/getTemporaryDirectory.h"
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUNX, RING1_FILESYSTEM_CONFIGURATION_BACKEND_OSX, or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS")
#endif

#include "Ring1/Memory/_Include.h"

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_getTemporaryDirectory
  (
    Ring1_FileSystem_Path** result
  )
{
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Linux_getTemporaryDirectory(result);
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Windows_getTemporaryDirectory(result);
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUNX, RING1_FILESYSTEM_CONFIGURATION_BACKEND_OSX, or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS")
#endif
}
