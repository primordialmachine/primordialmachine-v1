// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Operations.h"

#include "Ring2/Types.h"

static int g_referenceCount = 0;

Ring1_CheckReturn() Ring1_Result
Ring2_OperationsModule_startup
  (
  )
{
  if (0 == g_referenceCount) {
    if (Ring2_TypesModule_startup()) {
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
    Ring2_TypesModule_shutdown();
  }
  g_referenceCount--;
}
