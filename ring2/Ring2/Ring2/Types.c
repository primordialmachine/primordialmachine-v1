// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Types.h"


#include "Ring1/Conversion.h"


static int g_referenceCount = 0;

static Ring1_Conversion_ModuleHandle g_conversionModuleHandle =
  Ring1_Conversion_ModuleHandle_Invalid;

typedef struct Ring1_ModuleDependency {
  Ring1_Result (*startup)();
  void (*shutdown)();
} Ring1_ModuleDependency;

static const Ring1_ModuleDependency moduleDependencies[] = {
#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
  { &Ring2_ArrayModule_startup, &Ring2_ArrayModule_shutdown },
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
  { &Ring2_StringModule_startup, &Ring2_StringModule_shutdown },
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  { &Ring2_ObjectModule_startup, &Ring2_ObjectModule_shutdown },
#endif
};

static const size_t numberOfModuleDependencies = sizeof(moduleDependencies)/sizeof(Ring1_ModuleDependency);

static Ring1_Result startupModules() {
  for (size_t i = 0, n = numberOfModuleDependencies; i < n; ++i) {
    if (moduleDependencies[i].startup()) {
      while (i > 0) {
        moduleDependencies[--i].shutdown();
      }
      return Ring1_Result_Failure;    
    }
  }
  return Ring1_Result_Success;
}

static void shutdownModules() {
  for (size_t i = numberOfModuleDependencies; i > 0; i--) {
    moduleDependencies[i - 1].shutdown();
  }
}

Ring1_CheckReturn() Ring1_Result
Ring2_TypesModule_startup
  (
  )
{ 
  if (0 == g_referenceCount) {   
    g_conversionModuleHandle = Ring1_Conversion_ModuleHandle_acquire();
    if (!g_conversionModuleHandle) {
      return Ring1_Result_Failure;
    }
    if (startupModules()) {
      Ring1_Conversion_ModuleHandle_relinquish(g_conversionModuleHandle);
      g_conversionModuleHandle = Ring1_Conversion_ModuleHandle_Invalid;
      return Ring1_Result_Failure;   
    }
  }
  g_referenceCount++;
  return Ring1_Result_Success;
}

void
Ring2_TypesModule_shutdown
  (
  )
{
  if (1 == g_referenceCount) {
    shutdownModules();
    Ring1_Conversion_ModuleHandle_relinquish(g_conversionModuleHandle);
    g_conversionModuleHandle = Ring1_Conversion_ModuleHandle_Invalid;
  }
  g_referenceCount--;
}
