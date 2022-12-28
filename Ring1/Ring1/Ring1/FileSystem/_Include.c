// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/_Include.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/_Include.h"

#include "Ring1/FileSystem/Configuration.h"
#include <stdio.h>

#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Linux/receiveFileContents.h"
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Windows/receiveFileContents.h"
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI")
#endif

#include "Ring1/Memory/_Include.h"

static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_BeginDependencies()
  Ring1_Dependency(Ring1, Memory)
Ring1_EndDependencies()

Ring1_Module_Define(Ring1, FileSystem, initializeModule, uninitializeModule)

static Ring1_Result
initializeModule
  (
  )
{ return startupDependencies(); }

static void
uninitializeModule
  (
  )
{ shutdownDependencies(); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_receiveFileContents
  (
    Ring1_FileSystem_Path *path,
    void* context,
    Ring1_FileSystem_ReceiveCallback* receive
  )
{
  char* p; size_t n;
  if (Ring1_FileSystem_Path_toString(path, true, &p, &n)) {
    return Ring1_Result_Failure;
}
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  if (Ring1_FileSystem_Linux_receiveFileContents(p, context, receive)) {
    Ring1_Memory_deallocate(p);
    p = NULL;
    return Ring1_Result_Failure;
  }
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  if (Ring1_FileSystem_Windows_receiveFileContents(p, context, receive)) {
    Ring1_Memory_deallocate(p);
    p = NULL;
    return Ring1_Result_Failure;
  }
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUNX, RING1_FILESYSTEM_CONFIGURATION_BACKEND_OSX, or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS")
#endif
  Ring1_Memory_deallocate(p);
  p = NULL;
  return Ring1_Result_Success;
}
