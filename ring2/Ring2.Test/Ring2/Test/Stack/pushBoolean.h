// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Interpreter/Test/Stack/pushBoolean.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_INTERPRETER_TEST_STACK_PUSHBOOLEAN_H_INCLUDED)
#define MKX_INTERPRETER_TEST_STACK_PUSHBOOLEAN_H_INCLUDED

#include "Ring2/Test/Common.h"

void
Mkx_Interpreter_Test_Stack_pushBoolean
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

#endif // MKX_INTERPRETER_TEST_STACK_PUSHBOOLEAN_H_INCLUDED
