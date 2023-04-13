// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Instructions/Arithmetic.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Instructions/Arithmetic.h"
#undef RING2_PRIVATE


#include "Ring1/Status.h"
#define RING2_PRIVATE (1)
#include "Ring2/Operations.h"
#include "Ring2/Stack.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Instructions/GetOps.h"
#undef RING2_PRIVATE


void
Mkx_Interpreter_Instructions_add
  (
    Ring2_Context* context
  )
{ 
  Ring2_Value *x, *y;
  getTwo(context, &x, &y);
  
  // Dispatch.
  switch (Ring2_Value_getTag(x))
  {
    case Ring2_Value_Tag_Integer:
    {
      if (Ring2_Value_getTag(y) != Ring2_Value_Tag_Integer)
      {
        Ring1_Status_set(Ring1_Status_InvalidOperation);
        Ring2_jump();
      }
      Ring2_Integer_add(Ring2_Context_get(), x, y, x);
    } break;
    case Ring2_Value_Tag_Real64:
    {
      if (Ring2_Value_getTag(y) != Ring2_Value_Tag_Real64)
      {
        Ring1_Status_set(Ring1_Status_InvalidOperation);
        Ring2_jump();
      }
      Ring2_Value_setReal64(x, Ring2_Real64_add(Ring2_Context_get(), Ring2_Value_getReal64(x), Ring2_Value_getReal64(y)));
    } break;
    default:
    {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    } break;
  };

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(Ring2_Context_get(), 1);
}

void
Mkx_Interpreter_Instructions_subtract
  (
    Ring2_Context* context
  )
{
  Ring2_Value* x, * y;
  getTwo(context, &x, &y);

  // Dispatch.
  switch (Ring2_Value_getTag(x))
  {
  case Ring2_Value_Tag_Integer:
  {
    if (Ring2_Value_getTag(y) != Ring2_Value_Tag_Integer) 
    {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
    Ring2_Integer_subtract(context, x, y, x);
  } break;
  case Ring2_Value_Tag_Real64:
  {
    if (Ring2_Value_getTag(y) != Ring2_Value_Tag_Real64)
    {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
    Ring2_Value_setReal64(x, Ring2_Real64_subtract(context, Ring2_Value_getReal64(x), Ring2_Value_getReal64(y)));
  } break;
  default:
  {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
  };

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}

void
Mkx_Interpreter_Instructions_multiply
  (
    Ring2_Context* context
  )
{
  Ring2_Value* x, * y;
  getTwo(context, &x, &y);

  // Dispatch.
  switch (Ring2_Value_getTag(x))
  {
  case Ring2_Value_Tag_Integer:
  {
    if (Ring2_Value_getTag(y) != Ring2_Value_Tag_Integer)
    {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
    Ring2_Integer_multiply(context, x, y, x);
  } break;
  case Ring2_Value_Tag_Real64:
  {
    if (Ring2_Value_getTag(y) != Ring2_Value_Tag_Real64)
    {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
    Ring2_Value_setReal64(x, Ring2_Real64_multiply(context, Ring2_Value_getReal64(x), Ring2_Value_getReal64(y)));
  } break;
  default:
  {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
  };

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}

void
Mkx_Interpreter_Instructions_divide
  (
    Ring2_Context* context
  )
{
  Ring2_Value* x, * y;
  getTwo(context, &x, &y);

  // Dispatch.
  switch (Ring2_Value_getTag(x))
  {
  case Ring2_Value_Tag_Integer:
  {
    if (Ring2_Value_getTag(y) != Ring2_Value_Tag_Integer)
    {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
    Ring2_Integer_divide(context, x, y, x);
  } break;
  case Ring2_Value_Tag_Real64:
  {
    if (Ring2_Value_getTag(y) != Ring2_Value_Tag_Real64)
    {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
    Ring2_Value_setReal64(x, Ring2_Real64_divide(context, Ring2_Value_getReal64(x), Ring2_Value_getReal64(y)));
  } break;
  default:
  {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
  };

  // Pop the 2nd operand.
  Mkx_Interpreter_Stack_pop(context, 1);
}
