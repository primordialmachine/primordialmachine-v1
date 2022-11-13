// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Stack/pushInteger.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/Stack/pushInteger.h"

void
Mkx_Interpreter_Test_Stack_pushInteger
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  MKX_TEST_ASSERT_EQ(context, Mkx_Interpreter_Stack_getSize(Ring2_Context_get()), 0);
  for (Ring2_Integer i = 0, n = 16; i < n; ++i) {
    MKX_TEST_ASSERT_EQ(context, Mkx_Interpreter_Stack_getSize(Ring2_Context_get()), i + 0);
    Mkx_Interpreter_Stack_pushInteger(Ring2_Context_get(), i);
    MKX_TEST_ASSERT_EQ(context, Mkx_Interpreter_Stack_getSize(Ring2_Context_get()), i + 1);
  }
  Mkx_Interpreter_Stack_clear(Ring2_Context_get());
  MKX_TEST_ASSERT_EQ(context, Mkx_Interpreter_Stack_getSize(Ring2_Context_get()), 0);
}
