// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/All/_Include.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/All/_Include.h"

Ring1_BeginDependencies()
  Ring1_Dependency(Ring1, Memory)
  Ring1_Dependency(Ring1, Time)
  Ring1_Dependency(Ring1, Atom)
  Ring1_Dependency(Ring1, FileSystem)
  Ring1_Dependency(Ring1, Log)
Ring1_EndDependencies()

static Ring1_NoDiscardReturn() Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_Module_Define(Ring1, All, initializeModule, uninitializeModule)

static Ring1_Result
initializeModule
  (
  )
{
  if (startupDependencies()) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
uninitializeModule
  (
  )
{
  shutdownDependencies();
}
