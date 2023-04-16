// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Instructions/Arithmetic.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/Instructions/Arithmetic.h"

#include "Ring1/All/_Include.h"

static void
addReal
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Interpreter_Stack_pushReal(context, 12.);
  Mkx_Interpreter_Stack_pushReal(context, 7.);
  Mkx_Interpreter_Instructions_add(context);
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
  MKX_TEST_ASSERT_NEQ(context, value, NULL);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_isReal64(value), true);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_getReal64(value), 19.);
  Mkx_Interpreter_Stack_pop(context, 1);
}

static void
subtractReal
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Interpreter_Stack_pushReal(context, 12.);
  Mkx_Interpreter_Stack_pushReal(context, 7.);
  Mkx_Interpreter_Instructions_subtract(context);
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
  MKX_TEST_ASSERT_NEQ(context, value, NULL);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_isReal64(value), true);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_getReal64(value), 5.);
  Mkx_Interpreter_Stack_pop(context, 1);
}

static void
multiplyReal
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Interpreter_Stack_pushReal(context, 12.);
  Mkx_Interpreter_Stack_pushReal(context, 7.);
  Mkx_Interpreter_Instructions_multiply(context);
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
  MKX_TEST_ASSERT_NEQ(context, value, NULL);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_isReal64(value), true);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_getReal64(value), 84.);
  Mkx_Interpreter_Stack_pop(context, 1);
}

static void
divideReal
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Interpreter_Stack_pushReal(context, 12.);
  Mkx_Interpreter_Stack_pushReal(context, 3.);
  Mkx_Interpreter_Instructions_divide(context);
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
  MKX_TEST_ASSERT_NEQ(context, value, NULL);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_isReal64(value), true);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_getReal64(value), 4.);
  Mkx_Interpreter_Stack_pop(context, 1);
}

static void 
addInteger
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Interpreter_Stack_pushInteger(context, 12);
  Mkx_Interpreter_Stack_pushInteger(context, 7);
  Mkx_Interpreter_Instructions_add(context);
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
  MKX_TEST_ASSERT_NEQ(context, value, NULL);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_isInteger(value), true);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_getInteger(value), 19);
  Mkx_Interpreter_Stack_pop(context, 1);
}

static void
subtractInteger
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Interpreter_Stack_pushInteger(context, 12);
  Mkx_Interpreter_Stack_pushInteger(context, 7);
  Mkx_Interpreter_Instructions_subtract(context);
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
  MKX_TEST_ASSERT_NEQ(context, value, NULL);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_isInteger(value), true);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_getInteger(value), 5);
  Mkx_Interpreter_Stack_pop(context, 1);
}

static void
multiplyInteger
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Interpreter_Stack_pushInteger(context, 12);
  Mkx_Interpreter_Stack_pushInteger(context, 7);
  Mkx_Interpreter_Instructions_multiply(context);
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
  MKX_TEST_ASSERT_NEQ(context, value, NULL);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_isInteger(value), true);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_getInteger(value), 84);
  Mkx_Interpreter_Stack_pop(context, 1);
}

static void
divideInteger
  (
    Ring2_Context* context,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Interpreter_Stack_pushInteger(context, 12);
  Mkx_Interpreter_Stack_pushInteger(context, 3);
  Mkx_Interpreter_Instructions_divide(context);
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, 0);
  MKX_TEST_ASSERT_NEQ(context, value, NULL);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_isInteger(value), true);
  MKX_TEST_ASSERT_EQ(context, Ring2_Value_getInteger(value), 4);
  Mkx_Interpreter_Stack_pop(context, 1);
}

void
Ring2_Test_Instructions_registerArithmeticTests
  (
    Ring2_Tests *context
  )
{
  Ring2_String* prefix = Ring2_String_create("Ring2.Test.Instructions.Arithmetic.",
                                  crt_strlen("Ring2.Test.Instructions.Arithmetic."));

  {
    Ring2_Tests_addTest(context,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("addReal",
                                                          crt_strlen("addReal"))),
                        &addReal);
    Ring2_Tests_addTest(context,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("subtractReal",
                                                          crt_strlen("subtractReal"))),
                        &subtractReal);
    Ring2_Tests_addTest(context,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("multiplyReal",
                                                          crt_strlen("multiplyReal"))),
                        &multiplyReal);
    Ring2_Tests_addTest(context,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("divideReal",
                                                          crt_strlen("divideReal"))),
                        &divideReal);
    Ring2_Tests_addTest(context,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("addInteger",
                                                          crt_strlen("addInteger"))),
                        &addInteger);
    Ring2_Tests_addTest(context,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("subtractInteger",
                                                          crt_strlen("subtractInteger"))),
                        &subtractInteger);
    Ring2_Tests_addTest(context,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("multiplyInteger",
                                                          crt_strlen("multiplyInteger"))),
                        &multiplyInteger);
    Ring2_Tests_addTest(context,
                        Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                 Ring2_String_create("divideInteger",
                                                          crt_strlen("divideInteger"))),
                        &divideInteger);
  }
}
