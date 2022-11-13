// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Instructions/Relational.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Instructions/Relational.h"
#undef RING2_PRIVATE


#include "Ring1/Status.h"
#define RING2_PRIVATE (1)
#include "Ring2/Operations.h"
#include "Ring2/Stack.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Instructions/GetOps.h"
#undef RING2_PRIVATE


void
Mkx_Interpreter_Instructions_equalTo
  (
    Ring2_Context* context
  )
{
  Ring2_Value* x, * y;
  getTwo(context, &x, &y);

  // Dispatch.
  Ring2_Value_setBoolean(x, Ring2_Value_isEqualTo(context, x, y));

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}

void
Mkx_Interpreter_Instructions_notEqualTo
  (
    Ring2_Context* context
  )
{
  Ring2_Value *x, *y;
  getTwo(context, &x, &y);

  // Dispatch.
  Ring2_Value_setBoolean(x, Ring2_Value_isNotEqualTo(context, x, y));

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}

void
Mkx_Interpreter_Instructions_lowerThan
  (
    Ring2_Context* context
  )
{
  Ring2_Value *x, *y;
  getTwo(context, &x, &y);

  // Dispatch.
  Ring2_Value_isLowerThan(context, x, y, x);

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}

void
Mkx_Interpreter_Instructions_lowerThanOrEqualTo
  (
    Ring2_Context* context
  )
{
  Ring2_Value *x, *y;
  getTwo(context, &x, &y);

  // Dispatch.
  Ring2_Value_isLowerThanOrEqualTo(context, x, y, x);

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}

void
Mkx_Interpreter_Instructions_greaterThan
  (
    Ring2_Context* context
  )
{
  Ring2_Value* x, * y;
  getTwo(context, &x, &y);

  // Dispatch.
  Ring2_Value_isGreaterThan(context, x, y, x);

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}

void
Mkx_Interpreter_Instructions_greaterThanOrEqualTo
  (
    Ring2_Context* context
  )
{
  Ring2_Value* x, * y;
  getTwo(context, &x, &y);

  // Dispatch.
  Ring2_Value_isGreaterThanOrEqualTo(context, x, y, x);

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}
