// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Stack/pushReal.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/Stack/pushReal.h"

void
Mkx_Interpreter_Test_Stack_pushReal
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  MKX_TEST_ASSERT_EQ(context, Mkx_Interpreter_Stack_getSize(context), 0);
  for (Ring2_Integer i = 0, n = 16; i < n; ++i) {
    MKX_TEST_ASSERT_EQ(context, Mkx_Interpreter_Stack_getSize(context), i + 0);
    Mkx_Interpreter_Stack_pushReal(context, (Ring2_Real64)i);
    MKX_TEST_ASSERT_EQ(context, Mkx_Interpreter_Stack_getSize(context), i + 1);
  }
  Mkx_Interpreter_Stack_clear(context);
  MKX_TEST_ASSERT_EQ(context, Mkx_Interpreter_Stack_getSize(context), 0);
}
