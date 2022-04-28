/// @file Runtime/JumpTargetModule.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/JumpTargetModule.h"

static Machine_JumpTarget* g_jumpTargets = NULL;

Ring1_Result Machine_initializeJumpTargetModule() {
  g_jumpTargets = NULL;
  return Ring1_Result_Success;
}

void Machine_uninitializeJumpTargetModule()
{}

void Machine_pushJumpTarget(Machine_JumpTarget* jumpTarget) {
  jumpTarget->previous = g_jumpTargets;
  g_jumpTargets = jumpTarget;
}

void Machine_popJumpTarget() {
  g_jumpTargets = g_jumpTargets->previous;
}

NORETURN void Machine_jump() {
  longjmp(g_jumpTargets->environment, -1);
}
