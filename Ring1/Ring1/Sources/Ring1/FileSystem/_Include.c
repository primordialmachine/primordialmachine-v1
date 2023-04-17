// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/_Include.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/_Include.h"

#include "Ring1/FileSystem/Configuration.h"
#include <stdio.h>

#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LINUX == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Linux/receiveRegularContents.h"
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Windows/receiveRegularContents.h"
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
