// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/TypeName/Test/Main.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include <stdlib.h>
#include <stdio.h>
#include "Ring1/_Include.h"
#include "Ring1/Collections/_Include.h"
#include "Ring1/TypeName/_Include.h"
#include "Ring1/Test.h"

/// @param NAME
/// The name of the test.
/// @param EXPECTED
/// String denoting the string the Ring1_TypeName object returned by the
/// function denoted by @a GENERATOR is evaluating to.
/// @param GENERATOR
/// Name of the generator function.
#define Define(NAME, EXPECTED, GENERATOR) \
  void NAME(Ring1_Test_Context *ctx) { \
    Ring1_TypeName_ModuleHandle handle = Ring1_TypeName_ModuleHandle_acquire(); \
    RING1_TEST_ASSERT_NEQ(ctx, handle, Ring1_TypeName_ModuleHandle_Invalid); \
    if (!handle) { \
      return; \
    } \
    Ring1_TypeName *typeName; \
    if (GENERATOR(&typeName, ctx)) { \
      Ring1_TypeName_ModuleHandle_relinquish(handle); \
      handle = Ring1_TypeName_ModuleHandle_Invalid; \
      return; \
    } \
    char *received; \
    if (Ring1_TypeName_toString(&received, typeName)) { \
      Ring1_TypeName_unref(typeName); \
      Ring1_TypeName_ModuleHandle_relinquish(handle); \
      handle = Ring1_TypeName_ModuleHandle_Invalid; \
      return; \
    } \
    fprintf(stdout, "expected: %s, received: %s\n", EXPECTED, received); \
    RING1_TEST_ASSERT_EQ(ctx, crt_strcmp(received, EXPECTED), 0); \
    Ring1_TypeName_unref(typeName); \
    Ring1_Memory_deallocate(received); \
    Ring1_TypeName_ModuleHandle_relinquish(handle); \
    handle = Ring1_TypeName_ModuleHandle_Invalid; \
  }

/// @brief Unit test function validating scalar type name creation.
/// - creates scalar type "x"
/// - releases scalar type "x"
/// - creates scalar type "x"
/// - releases scalar type "x"
/// - creates a scalar type "x"
/// - returns the scalar type "x"
/// @param result A pointer to a <code>Ring1_TypeName *</code> variable.
/// @param ctx A pointer to the test context.
Ring1_CheckReturn() Ring1_Result
generateScalar
  (
    Ring1_TypeName **result,
    Ring1_Test_Context *ctx
  )
{
  Ring1_Result r;
  Ring1_TypeName* typeName;
  
  // (1)
  r = Ring1_TypeName_getOrCreateScalar(&typeName, "Ring1.TypeName.Test.A");
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return r;
  }
  Ring1_TypeName_unref(typeName);
  typeName = NULL;
  
  // (2)
  r = Ring1_TypeName_getOrCreateScalar(&typeName, "Ring1.TypeName.Test.A");
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return r;
  }
  Ring1_TypeName_unref(typeName);
  typeName = NULL;
  
  // (3)
  r = Ring1_TypeName_getOrCreateScalar(&typeName, "Ring1.TypeName.Test.A");
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return r;
  }
  *result = typeName;
  
  return Ring1_Result_Success;
}

Define(Ring1_TypeName_Test_Scalar, "Ring1.TypeName.Test.A", generateScalar)

/// @brief Unit test function validating 1d array type name creation.
/// @param result A pointer to a <code>Ring1_TypeName *</code> variable.
/// @param ctx A pointer to the test context.
Ring1_CheckReturn() Ring1_Result
generateArray1
  (
    Ring1_TypeName **result,
    Ring1_Test_Context *ctx
  )
{
  Ring1_Result r;
  Ring1_TypeName* scalar, *array;

  r = Ring1_TypeName_getOrCreateScalar(&scalar, "Ring1.TypeName.Test.A");
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return Ring1_Result_Failure;
  }

  r = Ring1_TypeName_getOrCreateArray(&array, 1, scalar);
  Ring1_TypeName_unref(scalar);
  scalar = NULL;
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return Ring1_Result_Failure;
  }

  *result = array;
  return Ring1_Result_Success;
}

Define(Ring1_TypeName_Test_Array1, "[Ring1.TypeName.Test.A]", generateArray1)

/// @brief Unit test function validating 2d array type name creation.
/// @param result A pointer to a <code>Ring1_TypeName *</code> variable.
/// @param ctx A pointer to the test context.
Ring1_CheckReturn() Ring1_Result
generateArray2
  (
    Ring1_TypeName **result,
    Ring1_Test_Context *ctx
  )
{
  Ring1_Result r;
  Ring1_TypeName* scalar, *array;

  r = Ring1_TypeName_getOrCreateScalar(&scalar, "Ring1.TypeName.Test.A");
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return Ring1_Result_Failure;
  }

  r = Ring1_TypeName_getOrCreateArray(&array, 2, scalar);
  Ring1_TypeName_unref(scalar);
  scalar = NULL;
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return Ring1_Result_Failure;
  }

  *result = array;
  return Ring1_Result_Success;
}

Define(Ring1_TypeName_Test_Array2, "[[Ring1.TypeName.Test.A]]", generateArray2)

static void
Ring1_TypeName_Test_InvalidTypeName
  (
    Ring1_Test_Context *ctx
  )
{
  Ring1_TypeName_ModuleHandle handle = Ring1_TypeName_ModuleHandle_acquire();
  RING1_TEST_ASSERT_NEQ(ctx, handle, Ring1_TypeName_ModuleHandle_Invalid);
  if (!handle) {
    return;
  }
  Ring1_TypeName* typeName;
  Ring1_Result r;
  
  Ring1_Status_set(Ring1_Status_Success);
  r = Ring1_TypeName_getOrCreateScalar(&typeName, ".");
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_InvalidSyntactics);
  if (r != Ring1_Result_Failure) {
    Ring1_TypeName_unref(typeName);
    return;
  }  

  r = Ring1_TypeName_getOrCreateScalar(&typeName, "a.");
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_InvalidSyntactics);
  if (r != Ring1_Result_Failure) {
    Ring1_TypeName_unref(typeName);
    return;
  }  

  r = Ring1_TypeName_getOrCreateScalar(&typeName, "1.1");
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_InvalidSyntactics);
  if (r != Ring1_Result_Failure) {
    Ring1_TypeName_unref(typeName);
    return;
  }  

  Ring1_TypeName_ModuleHandle_relinquish(handle);
  handle = Ring1_TypeName_ModuleHandle_Invalid;
}

Ring1_Result
Ring1_TypeName_runAll
  (
  )
{
  Ring1_Test_Context* ctx = NULL;
  if (Ring1_Test_Context_create(&ctx)) {
    return Ring1_Result_Failure;
  }
  if (   Ring1_Test_Context_addTest(ctx, "Ring1.TypeName.Test.Scalar", &Ring1_TypeName_Test_Scalar)
      || Ring1_Test_Context_addTest(ctx, "Ring1.TypeName.Test.Array1", &Ring1_TypeName_Test_Array1)
      || Ring1_Test_Context_addTest(ctx, "Ring1.TypeName.Test.Array2", &Ring1_TypeName_Test_Array2)
      || Ring1_Test_Context_addTest(ctx, "Ring1.TypeName.Test.InvalidTypeName", &Ring1_TypeName_Test_InvalidTypeName)) {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_runAllTests(ctx)) {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return Ring1_Result_Failure;
  }
  Ring1_Test_Context_destroy(ctx);
  ctx = NULL;
  return Ring1_Result_Success;
}

int
main
  (
  )
{
  if (Ring1_TypeName_runAll()) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
