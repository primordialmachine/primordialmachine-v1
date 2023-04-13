// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Instructions/Concatenate.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Instructions/Concatenate.h"
#undef RING2_PRIVATE


#include "Ring1/Status.h"
#define RING2_PRIVATE (1)
#include "Ring2/Operations.h"
#include "Ring2/Stack.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Instructions/GetOps.h"
#undef RING2_PRIVATE


void
Mkx_Interpreter_Instructions_concatenate
  (
    Ring2_Context* context
  )
{
  Ring2_Value *x, *y;
  getTwo(context, &x, &y);

  // Dispatch.
  switch (Ring2_Value_getTag(x))
  {
  case Ring2_Value_Tag_String:
  {
    if (Ring2_Value_getTag(y) != Ring2_Value_Tag_String)
    {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
    Ring2_Value_setString(x, Ring2_String_concatenate(context, Ring2_Value_getString(x), Ring2_Value_getString(y)));
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
