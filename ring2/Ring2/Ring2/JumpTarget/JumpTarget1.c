// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/JumpTarget/JumpTarget1.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/JumpTarget/JumpTarget1.h"

static Ring2_JumpTarget* g_jumpTargets = NULL;
static int g_referenceCount = 0;

Ring1_CheckReturn() Ring1_Result
Ring2_JumpTargetModule_startup
  (
  )
{
  if (g_referenceCount == 0) {
    g_jumpTargets = NULL;
  }
  g_referenceCount++;
  return Ring1_Result_Success;
}

void
Ring2_JumpTargetModule_shutdown
  (
  )
{
  if (1 == g_referenceCount) {
    /*Intentionally empty.*/
  }
  g_referenceCount--;
}

void
Ring2_pushJumpTarget
  (
    Ring2_JumpTarget* jumpTarget
  )
{
  jumpTarget->previous = g_jumpTargets;
  g_jumpTargets = jumpTarget;
}

void
Ring2_popJumpTarget
  (
  )
{
  g_jumpTargets = g_jumpTargets->previous;
}

Ring1_NoReturn() void
Ring2_jump()
{
  longjmp(g_jumpTargets->environment, -1);
}
