// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations.h"

#include "Ring2/Types.h"
#include "Ring2/Operations/_Buffer.h"

Ring1_BeginDependencies()
  Ring1_Dependency(Ring2, TypesModule)
Ring1_EndDependencies()

static Ring1_CheckReturn() Ring1_Result
Ring2_OperationsModule_startup
  (
  )
{
  if (Ring2_Operations__Buffer_startup()) {
    return Ring1_Result_Failure;
  }
  if (startupDependencies()) {
    Ring2_Operations__Buffer_shutdown();
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
Ring2_OperationsModule_shutdown
  (
  )
{
  shutdownDependencies();
  Ring2_Operations__Buffer_shutdown();
}

Ring1_Module_Define(Ring2, OperationsModule, Ring2_OperationsModule_startup, Ring2_OperationsModule_shutdown)
