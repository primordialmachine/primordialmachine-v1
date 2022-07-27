// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations.h"

#include "Ring2/Types.h"
#include "Ring2/JumpTarget.h"
#include "Ring1/Conversion.h"

static int g_referenceCount = 0;

#include "Ring1/Conversion.h"

static Ring1_Conversion_ModuleHandle g_conversionModuleHandle =
  Ring1_Conversion_ModuleHandle_Invalid;

Ring1_CheckReturn() Ring1_Result
Ring2_OperationsModule_startup
  (
  )
{
  if (0 == g_referenceCount) {
    g_conversionModuleHandle = Ring1_Conversion_ModuleHandle_acquire();
    if (!g_conversionModuleHandle) {
      return Ring1_Result_Failure;
    }
    if (Ring2_TypesModule_startup()) {
      Ring1_Conversion_ModuleHandle_relinquish(g_conversionModuleHandle);
      g_conversionModuleHandle = Ring1_Conversion_ModuleHandle_Invalid;
      return Ring1_Result_Failure;
    }
    if (Ring2_JumpTargetModule_startup()) {
      Ring2_TypesModule_shutdown();
      Ring1_Conversion_ModuleHandle_relinquish(g_conversionModuleHandle);
      g_conversionModuleHandle = Ring1_Conversion_ModuleHandle_Invalid;
      return Ring1_Result_Failure;
    }
  }
  g_referenceCount++;
  return Ring1_Result_Success;
}

void
Ring2_OperationsModule_shutdown
  (
  )
{
  if (1 == g_referenceCount) {
    Ring2_JumpTargetModule_shutdown();
    Ring2_TypesModule_shutdown();
    Ring1_Conversion_ModuleHandle_relinquish(g_conversionModuleHandle);
    g_conversionModuleHandle = Ring1_Conversion_ModuleHandle_Invalid;
  }
  g_referenceCount--;
}
