// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/JumpTarget/JumpTarget1.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/JumpTarget/JumpTarget1.h"
#undef RING2_PRIVATE

static Ring2_JumpTarget* g_jumpTargets = NULL;

Ring1_CheckReturn() Ring1_Result
Ring2_JumpTargetModule_startup
  (
  )
{
  g_jumpTargets = NULL;
  return Ring1_Result_Success;
}

void
Ring2_JumpTargetModule_shutdown
  (
  )
{ }

Ring1_Module_Define(Ring2, JumpTargetModule, Ring2_JumpTargetModule_startup, Ring2_JumpTargetModule_shutdown)

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
