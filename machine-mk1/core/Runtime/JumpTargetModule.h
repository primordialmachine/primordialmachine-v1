/// @file Runtime/JumpTargetModule.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_JUMPTARGETMODULE_H_INCLUDED)
#define MACHINE_RUNTIME_JUMPTARGETMODULE_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "_Eal.h"
#include "Runtime/Status.h"



Machine_StatusValue Machine_initializeJumpTargetModule();

void Machine_uninitializeJumpTargetModule();

/// @brief C-level representation of a jump target.
typedef struct Machine_JumpTarget Machine_JumpTarget;

struct Machine_JumpTarget {
  Machine_JumpTarget* previous;
  jmp_buf environment;
};

///  @brief Push a jump target on the jump target stack.
/// @param jumpTarget A pointer to the jump target.
void Machine_pushJumpTarget(Machine_JumpTarget* jumpTarget);

/// @brief Pop a jump target from the jump target stack.
void Machine_popJumpTarget();

/// @brief Jump to the top of the jump target stack.
/// @warning Undefined if the jump target stack is empty.
NORETURN void Machine_jump();



#endif // MACHINE_RUNTIME_JUMPTARGETMODULE_H_INCLUDED
