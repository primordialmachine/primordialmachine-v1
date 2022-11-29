// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Value.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/Value.h"

#include "Ring1/Intrinsic.h"
#include "Ring1/_Include.h"
#include "Ring2/_Include.h"
#include "Ring2/Test/Fixtures/ForeignProcedure.h"
#include "Ring2/Test/Fixtures/Object.h"

static void
testArray
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerArray(Ring2_ArrayHeap_createArray(Ring2_Context_get(), 0));
  RING2_TEST_ASSERT(Ring2_Value_isArray(&v));

  Ring2_Value_setVoid(&v, Ring2_Void_Void);
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));

  Ring2_Value_setArray(&v, Ring2_ArrayHeap_createArray(Ring2_Context_get(), 0));
  RING2_TEST_ASSERT(Ring2_Value_isArray(&v));
}

static void
testBoolean
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerBoolean(false);
  RING2_TEST_ASSERT(Ring2_Value_isBoolean(&v));

  Ring2_Value_setVoid(&v, Ring2_Void_Void);
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));

  Ring2_Value_setBoolean(&v, false);
  RING2_TEST_ASSERT(Ring2_Value_isBoolean(&v));
}

static void
testForeignProcedure
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerForeignProcedure(&Ring2_Test_Fixtures_a);
  RING2_TEST_ASSERT(Ring2_Value_isForeignProcedure(&v));

  Ring2_Value_setVoid(&v, Ring2_Void_Void);
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));

  Ring2_Value_setForeignProcedure(&v, &Ring2_Test_Fixtures_a);
  RING2_TEST_ASSERT(Ring2_Value_isForeignProcedure(&v));
}

static void
testInteger
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerInteger(0);
  RING2_TEST_ASSERT(Ring2_Value_isInteger(&v));

  Ring2_Value_setVoid(&v, Ring2_Void_Void);
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));

  Ring2_Value_setInteger(&v, 0);
  RING2_TEST_ASSERT(Ring2_Value_isInteger(&v));
}

static void
testObject
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerObject(Ring1_cast(Machine_Object *, Ring2_Test_Fixtures_A_create()));
  RING2_TEST_ASSERT(Ring2_Value_isObject(&v));

  Ring2_Value_setVoid(&v, Ring2_Void_Void);
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));

  Ring2_Value_setObject(&v, Ring1_cast(Machine_Object *,Ring2_Test_Fixtures_A_create()));
  RING2_TEST_ASSERT(Ring2_Value_isObject(&v));
}

static void
testReal32
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerReal32(0);
  RING2_TEST_ASSERT(Ring2_Value_isReal32(&v));

  Ring2_Value_setVoid(&v, Ring2_Void_Void);
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));

  Ring2_Value_setReal32(&v, 0);
  RING2_TEST_ASSERT(Ring2_Value_isReal32(&v));
}

static void
testReal64
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerReal64(0);
  RING2_TEST_ASSERT(Ring2_Value_isReal64(&v));

  Ring2_Value_setVoid(&v, Ring2_Void_Void);
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));

  Ring2_Value_setReal64(&v, 0);
  RING2_TEST_ASSERT(Ring2_Value_isReal64(&v));
}

static void
testString
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerString(Ring2_String_create("", crt_strlen("")));
  RING2_TEST_ASSERT(Ring2_Value_isString(&v));

  Ring2_Value_setVoid(&v, Ring2_Void_Void);
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));

  Ring2_Value_setString(&v, Ring2_String_create("", crt_strlen("")));
  RING2_TEST_ASSERT(Ring2_Value_isString(&v));
}

static void
testVoid
  (
    Ring2_Context* ctx,
    Ring2_Value *result,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerVoid();
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));

  Ring2_Value_setVoid(&v, Ring2_Void_Void);
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));

  Ring2_Value_setVoid(&v, Ring2_Void_Void);
  RING2_TEST_ASSERT(Ring2_Value_isVoid(&v));
}

void
Ring2_Test_registerValueTests
  (
    Ring2_Tests *tests
  )
{
  Ring2_String* prefix = Ring2_String_create("Ring2.Test.ValueTest",
                                  crt_strlen("Ring2.Test.ValueTest"));
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("Array",
                                                                             crt_strlen("Array"))),
                      &testArray);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("Boolean",
                                                                             crt_strlen("Boolean"))),
                      &testBoolean);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("ForeignProcedure",
                                                                             crt_strlen("ForeignProcedure"))),
                      &testForeignProcedure);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("Integer",
                                                                             crt_strlen("Integer"))),
                      &testInteger);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("Object",
                                                                             crt_strlen("Object"))),
                      &testObject);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("Real32",
                                                                             crt_strlen("Real32"))),
                      &testReal32);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("Real64",
                                                                             crt_strlen("Real64"))),
                      &testReal64);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("String",
                                                                             crt_strlen("String"))),
                      &testString);
  Ring2_Tests_addTest(tests,
                      Ring2_String_concatenate(Ring2_Context_get(), prefix,
                                                                    Ring2_String_create("Void",
                                                                             crt_strlen("Void"))),
                      &testVoid);
}
