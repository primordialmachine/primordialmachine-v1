/// @file Runtime/JumpTargetModule.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/JumpTargetModule.h"

Ring1_CheckReturn() Ring1_Result Machine_initializeJumpTargetModule() {
  return Ring2_JumpTargetModule_startup();
}

void Machine_uninitializeJumpTargetModule() {
  Ring2_JumpTargetModule_shutdown();
}
