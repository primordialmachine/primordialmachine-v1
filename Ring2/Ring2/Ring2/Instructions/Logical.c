// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Instructions/Logical.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Instructions/Logical.h"
#undef RING2_PRIVATE


#include "Ring1/Status.h"
#define RING2_PRIVATE (1)
#include "Ring2/Operations.h"
#include "Ring2/Stack.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Instructions/GetOps.h"
#undef RING2_PRIVATE


void
Mkx_Interpreter_Instructions_and
  (
    Ring2_Context* context
  )
{
  Ring2_Value* x, * y;
  getTwo(context, &x, &y);

  // Assert 1st operand is of type Boolean.
  if (!Ring2_Value_isBoolean(x)) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }

  // Assert 2nd operand is of type Boolean.
  if (!Ring2_Value_isBoolean(y)) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  
  // Assign the result to x.
  Ring2_Boolean_and(context, x, y, x);

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}

void
Mkx_Interpreter_Instructions_or
  (
    Ring2_Context* context
  )
{
  Ring2_Value* x, * y;
  getTwo(context, &x, &y);

  // Assert 1st operand is of type Boolean.
  if (!Ring2_Value_isBoolean(x)) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }

  // Assert 2nd operand is of type Boolean.
  if (!Ring2_Value_isBoolean(y)) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }

  // Assign the result to x.
  Ring2_Boolean_or(context, x, y, x);
  
  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}
