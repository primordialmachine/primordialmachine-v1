// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/JumpTarget/JumpTarget1.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_JUMPTARGET_JUMPTARGET1_H_INCLUDED)
#define RING2_JUMPTARGET_JUMPTARGET1_H_INCLUDED

#include "Ring2/_header.h.i"
#include <setjmp.h>

/// @brief Starts up the "jump target" module.
Ring1_CheckReturn() Ring1_Result
Ring2_JumpTargetModule_startup
  (
  );

/// @brief Shuts down the "jump target" module.
void
Ring2_JumpTargetModule_shutdown
  (
  );

/// @brief C-level representation of a jump target.
typedef struct Ring2_JumpTarget Ring2_JumpTarget;

struct Ring2_JumpTarget
{
  Ring2_JumpTarget* previous;
  jmp_buf environment;
};

/// @brief Push a jump target on the jump target stack.
/// @param jumpTarget A pointer to the jump target.
void
Ring2_pushJumpTarget
  (
    Ring2_JumpTarget* jumpTarget
  );

/// @brief Pop a jump target from the jump target stack.
void
Ring2_popJumpTarget
  (
  );

/// @brief Jump to the top of the jump target stack.
/// @warning Undefined if the jump target stack is empty.
Ring1_NoReturn() void
Ring2_jump
  (
  );

#endif // RING2_JUMPTARGET_JUMPTARGET1_H_INCLUDED
