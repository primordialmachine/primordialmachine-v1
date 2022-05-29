// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Types.h"

static int g_referenceCount = 0;

Ring1_CheckReturn() Ring1_Result
Ring2_TypesModule_startup
  (
  )
{ 
  if (0 == g_referenceCount) {
    
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
  
  }
  g_referenceCount--;
}
