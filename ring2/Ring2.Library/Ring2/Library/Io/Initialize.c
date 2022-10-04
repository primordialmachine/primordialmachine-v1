// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/Initialize.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Io/Initialize.h"


#include "Ring1/Status.h"
#include "Ring1/FileSystem.h"
#include "Ring2/_Include.h"


static Ring1_FileSystem_ModuleHandle g_moduleHandle = Ring1_FileSystem_ModuleHandle_Invalid;

static void
onUninitializeStaticVariables
  (
  )
{
  Ring1_FileSystem_ModuleHandle_relinquish(g_moduleHandle);
  g_moduleHandle = Ring1_FileSystem_ModuleHandle_Invalid;
}

void
Machine_Io_initialize
  (
  )
{
  if (Ring1_FileSystem_ModuleHandle_Invalid == g_moduleHandle) {
    g_moduleHandle = Ring1_FileSystem_ModuleHandle_acquire();
    if (!g_moduleHandle) {
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    if (Machine_registerStaticVariables(&onUninitializeStaticVariables)) {
      Ring1_FileSystem_ModuleHandle_relinquish(g_moduleHandle);
      g_moduleHandle = Ring1_FileSystem_ModuleHandle_Invalid;
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
  }
}
