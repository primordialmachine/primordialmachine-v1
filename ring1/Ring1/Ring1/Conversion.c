// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Conversion.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Conversion.h"

#include "Ring1/Conversion/_Buffer.h"
#include "Ring1/Memory.h"

static Ring1_CheckReturn() Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_Module_Define(Conversion, initializeModule, uninitializeModule)

static Ring1_Memory_ModuleHandle g_memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;

static Ring1_CheckReturn() Ring1_Result
initializeModule
  (
  )
{
  g_memoryModuleHandle = Ring1_Memory_ModuleHandle_acquire();
  if (Ring1_Unlikely(!g_memoryModuleHandle)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Conversion__Buffer_startup()) {
    Ring1_Memory_ModuleHandle_relinquish(g_memoryModuleHandle);
    g_memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
uninitializeModule
  (
  )
{
  Ring1_Conversion__Buffer_shutdown();
  Ring1_Memory_ModuleHandle_relinquish(g_memoryModuleHandle);
  g_memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;
}
