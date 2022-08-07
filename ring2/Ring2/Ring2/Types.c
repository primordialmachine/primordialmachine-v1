// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Types.h"

#include "Ring2/Types/String.h"

static int g_referenceCount = 0;

typedef void (Ring2_ModuleShutdownCallback)();

static size_t numberOfModules = 0;
static Ring2_ModuleShutdownCallback *moduleShutdownCallbacks[2] = { NULL };

static void shutdownModules() {
  while (numberOfModules > 0) {
    moduleShutdownCallbacks[--numberOfModules]();
  }
}

Ring1_CheckReturn() Ring1_Result
Ring2_TypesModule_startup
  (
  )
{ 
  if (0 == g_referenceCount) {   
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
    if (Ring2_StringModule_startup()) {
      shutdownModules();
      return Ring1_Result_Failure;
    }
    moduleShutdownCallbacks[numberOfModules++] = &Ring2_StringModule_shutdown;
#endif // Ring2_Configuration_withString
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
  }
  g_referenceCount--;
}
