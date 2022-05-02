/// @file Runtime/JumpTargetModule.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_JUMPTARGETMODULE_H_INCLUDED)
#define MACHINE_RUNTIME_JUMPTARGETMODULE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "Ring2/JumpTargetModule.h"

Ring1_CheckReturn() Ring1_Result Machine_initializeJumpTargetModule();

void Machine_uninitializeJumpTargetModule();

/// @brief C-level representation of a jump target.
#define Machine_JumpTarget Ring2_JumpTarget

/// @brief Push a jump target on the jump target stack.
/// @param jumpTarget A pointer to the jump target.
#define Machine_pushJumpTarget(X) Ring2_pushJumpTarget(X)

/// @brief Pop a jump target from the jump target stack.
#define Machine_popJumpTarget() Ring2_popJumpTarget()

/// @brief Jump to the top of the jump target stack.
/// @warning Undefined if the jump target stack is empty.
#define Machine_jump() Ring2_jump()

#endif // MACHINE_RUNTIME_JUMPTARGETMODULE_H_INCLUDED
