// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Instructions/Logical.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/Instructions/Logical.h"

#include "Ring1/All/_Include.h"


static void
doAnd
  (
    Ring2_Context* context,
    Ring2_Boolean x,
    Ring2_Boolean y,
    Ring2_Boolean z
  )
{
  Mkx_Interpreter_Stack_pushBoolean(context, x);
  Mkx_Interpreter_Stack_pushBoolean(context, y);
  Mkx_Interpreter_Instructions_and(context);
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
  MKX_TEST_ASSERT_NEQ(context, value, NULL);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_isBoolean(value), true);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_getBoolean(value), z);
  Mkx_Interpreter_Stack_pop(context, 1);
}

static void
doOr
  (
    Ring2_Context* context,
    Ring2_Boolean x,
    Ring2_Boolean y,
    Ring2_Boolean z
  )
{
  Mkx_Interpreter_Stack_pushBoolean(context, x);
  Mkx_Interpreter_Stack_pushBoolean(context, y);
  Mkx_Interpreter_Instructions_or(context);
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
  MKX_TEST_ASSERT_NEQ(context, value, NULL);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_isBoolean(value), true);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_getBoolean(value), z);
  Mkx_Interpreter_Stack_pop(context, 1);
}

static void
Mkx_Interpreter_Test_Instructions_Logical_and
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  doAnd(context, Ring2_Boolean_False, Ring2_Boolean_False, Ring2_Boolean_False);
  doAnd(context, Ring2_Boolean_False, Ring2_Boolean_True, Ring2_Boolean_False);
  doAnd(context, Ring2_Boolean_True, Ring2_Boolean_False, Ring2_Boolean_False);
  doAnd(context, Ring2_Boolean_True, Ring2_Boolean_True, Ring2_Boolean_True);
}

static void
Mkx_Interpreter_Test_Instructions_Logical_or
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  doOr(context, Ring2_Boolean_False, Ring2_Boolean_False, Ring2_Boolean_False);
  doOr(context, Ring2_Boolean_False, Ring2_Boolean_True, Ring2_Boolean_True);
  doOr(context, Ring2_Boolean_True, Ring2_Boolean_False, Ring2_Boolean_True);
  doOr(context, Ring2_Boolean_True, Ring2_Boolean_True, Ring2_Boolean_True);
}

void
Ring2_Test_Instructions_registerLogicalTests
  (
    Ring2_Tests* tests
  )
{
  Ring2_String* prefix = Ring2_String_create("Ring2.Test.Instructions.Logical.",
                                  crt_strlen("Ring2.Test.Instructions.Logical."));
  
  {
    Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("and",
                                                                             crt_strlen("and"))),
                      &Mkx_Interpreter_Test_Instructions_Logical_and);
    Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("or",
                                                                             crt_strlen("or"))),
                      &Mkx_Interpreter_Test_Instructions_Logical_or);
  }
}
