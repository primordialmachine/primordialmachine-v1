// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Instructions/Affirmate.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Instructions/Affirmate.h"
#undef RING2_PRIVATE


#include "Ring1/Status.h"
#define RING2_PRIVATE (1)
#include "Ring2/Operations.h"
#include "Ring2/Stack.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Instructions/GetOps.h"
#undef RING2_PRIVATE


void
Mkx_Interpreter_Instructions_affirmate
  (
    Ring2_Context* context
  )
{
  // Get the single operand.
  Ring2_Value* x = Mkx_Interpreter_Stack_getAt(context, 0);
  if (!x) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }

  // Dispatch.
  switch (Ring2_Value_getTag(x))
  {
  case Ring2_Value_Tag_Boolean: {
    Ring2_Value_setBoolean(x, Ring2_Boolean_affirmate(context, Ring2_Value_getBoolean(x)));
  } break;
  case Ring2_Value_Tag_Integer: {
    Ring2_Value_setInteger(x, Ring2_Integer_affirmate(context, Ring2_Value_getInteger(x)));
  } break;
  case Ring2_Value_Tag_Real64: {
    Ring2_Value_setReal64(x, Ring2_Real64_affirmate(context, Ring2_Value_getReal64(x)));
  } break;
  default: {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  } break;
  };
}
