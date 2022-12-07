// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Atom/Test/Main.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include <stdlib.h>
#include "Ring1/All/_Include.h"
#include "Ring1/Test.h"

/// @brief Unit test asserting atoms for equivalent strings are equivalent.
/// @param ctx A pointer to the test context.
/// @todo The atom module (un)initialization could (and should) be performed in a test (suite) startup/test (suite) shutdown method.
static Ring1_NoDiscardResult() Ring1_Result
Ring1_Atom_Test_equal
  (
    Ring1_Test_Context *ctx
  )
{
  Ring1_Atom_ModuleHandle handle = Ring1_Atom_ModuleHandle_Invalid;
  handle = Ring1_Atom_ModuleHandle_acquire();
  RING1_TEST_ASSERT_NEQ(ctx, handle, Ring1_Atom_ModuleHandle_Invalid);
  if (!handle) {
    return Ring1_Result_Failure;
  }
  Ring1_Atom* x0;
  int result;
  result = Ring1_Atom_getOrCreate(&x0, "x", crt_strlen("x"));
  RING1_TEST_ASSERT_EQ(ctx, result, Ring1_Result_Success);
  if (result) {
    Ring1_Atom_unreference(x0);
    x0 = NULL;
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  Ring1_Atom* x1;
  result = Ring1_Atom_getOrCreate(&x1, "x", crt_strlen("x"));
  RING1_TEST_ASSERT_EQ(ctx, result, Ring1_Result_Success);
  if (result) {
    Ring1_Atom_unreference(x0);
    x0 = NULL;
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  // Must be equal.
  RING1_TEST_ASSERT_EQ(ctx, x0, x1);
  if (x0 != x1) {
    Ring1_Atom_unreference(x1);
    x1 = NULL;
    Ring1_Atom_unreference(x0);
    x0 = NULL;
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  Ring1_Atom_unreference(x1);
  x1 = NULL;
  Ring1_Atom_unreference(x0);
  x0 = NULL;
  Ring1_Atom_ModuleHandle_relinquish(handle);
  handle = Ring1_Atom_ModuleHandle_Invalid;
  return Ring1_Result_Success;
}

/// @brief Unit test function asserting atoms for non-equivalent strings are non-equivalent.
/// @param ctx A pointer to the test context.
/// @todo The atom module (un)initialization could (and should) be performed in a test (suite) startup/test (suite) shutdown method.
static Ring1_NoDiscardResult() Ring1_Result
Ring1_Atom_Test_notEqual
  (
    Ring1_Test_Context *ctx
  )
{
  Ring1_Atom_ModuleHandle handle = Ring1_Atom_ModuleHandle_Invalid;
  handle = Ring1_Atom_ModuleHandle_acquire();
  RING1_TEST_ASSERT_NEQ(ctx, handle, Ring1_Atom_ModuleHandle_Invalid);
  if (!handle) {
    return Ring1_Result_Failure;
  }
  Ring1_Atom* x0;
  int result;
  result = Ring1_Atom_getOrCreate(&x0, "x", crt_strlen("x"));
  RING1_TEST_ASSERT_EQ(ctx, result, Ring1_Result_Success);
  if (result) {
    Ring1_Atom_unreference(x0);
    x0 = NULL;
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  Ring1_Atom* x1;
  result = Ring1_Atom_getOrCreate(&x1, "y", crt_strlen("y"));
  RING1_TEST_ASSERT_EQ(ctx, result, Ring1_Result_Success);
  if (result) {
    Ring1_Atom_unreference(x0);
    x0 = NULL;
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  // Must not be equal.
  RING1_TEST_ASSERT_NEQ(ctx, x0, x1);
  if (x0 == x1) {
    Ring1_Atom_unreference(x1);
    x1 = NULL;
    Ring1_Atom_unreference(x0);
    x0 = NULL;
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  Ring1_Atom_unreference(x1);
  x1 = NULL;
  Ring1_Atom_unreference(x0);
  x0 = NULL;
  Ring1_Atom_ModuleHandle_relinquish(handle);
  handle = Ring1_Atom_ModuleHandle_Invalid;
  return Ring1_Result_Success;
}

static void
onFree
  (
    char **s
  )
{
  free(*s);
}

/// @brief Unit test function asserting creation of many atoms for non-equivalent strings are non-equivalent.
/// @param ctx A pointer to the test context.
/// @todo The atom module (un)initialization could (and should) be performed in a test (suite) startup/test (suite) shutdown method.
/// @todo Actually implement the test according to its description.
static Ring1_NoDiscardResult() Ring1_Result
Ring1_Atom_Test_many
  (
    Ring1_Test_Context *ctx
  )
{
  Ring1_Atom_ModuleHandle handle = Ring1_Atom_ModuleHandle_Invalid;
  handle = Ring1_Atom_ModuleHandle_acquire();
  RING1_TEST_ASSERT_NEQ(ctx, handle, Ring1_Atom_ModuleHandle_Invalid);
  if (!handle) {
    return Ring1_Result_Failure;
  }
  Ring1_PointerList strings;
  int result;
  result = Ring1_PointerList_initialize(&strings, NULL, &onFree);
  RING1_TEST_ASSERT_EQ(ctx, result, Ring1_Result_Success);
  if (result) {
    return Ring1_Result_Failure;
  }
  char* string = crt_strdup("Hello, World!");
  RING1_TEST_ASSERT_NOTNULL(ctx, string);
  if (!string) {
    Ring1_PointerList_uninitialize(&strings);
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  result = Ring1_PointerList_insertBack(&strings, string);
  RING1_TEST_ASSERT_EQ(ctx, result, Ring1_Result_Success);
  if (result) {
    crt_free(string);
    Ring1_PointerList_uninitialize(&strings);
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  Ring1_Atom* x0;
  result = Ring1_Atom_getOrCreate(&x0, "x", crt_strlen("x"));
  RING1_TEST_ASSERT_EQ(ctx, result, Ring1_Result_Success);
  if (result) {
    Ring1_Atom_unreference(x0);
    x0 = NULL;
    Ring1_PointerList_uninitialize(&strings);
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  Ring1_Atom* x1;
  result = Ring1_Atom_getOrCreate(&x1, "y", crt_strlen("y"));
  RING1_TEST_ASSERT_EQ(ctx, result, Ring1_Result_Success);
  if (result) {
    Ring1_Atom_unreference(x0);
    x0 = NULL;
    Ring1_PointerList_uninitialize(&strings);
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  // Must not be equal.
  RING1_TEST_ASSERT_NEQ(ctx, x0, x1);
  if (x0 == x1) {
    Ring1_Atom_unreference(x1);
    x1 = NULL;
    Ring1_Atom_unreference(x0);
    x0 = NULL;
    Ring1_PointerList_uninitialize(&strings);
    Ring1_Atom_ModuleHandle_relinquish(handle);
    handle = Ring1_Atom_ModuleHandle_Invalid;
    return Ring1_Result_Failure;
  }
  Ring1_Atom_unreference(x1);
  x1 = NULL;
  Ring1_Atom_unreference(x0);
  x0 = NULL;
  Ring1_PointerList_uninitialize(&strings);
  Ring1_Atom_ModuleHandle_relinquish(handle);
  handle = Ring1_Atom_ModuleHandle_Invalid;
  return Ring1_Result_Success;
}

Ring1_Result
Ring1_Atom_runAll
  (
  )
{
  Ring1_Test_Context* ctx = NULL;
  if (Ring1_Test_Context_create(&ctx)) {
    return Ring1_Result_Failure;
  }
  if (   Ring1_Test_Context_addTest(ctx, "Ring1.Atom.Test.Many", &Ring1_Atom_Test_many)
      || Ring1_Test_Context_addTest(ctx, "Ring1.Atom.Test.Equal", &Ring1_Atom_Test_equal)
      || Ring1_Test_Context_addTest(ctx, "Ring1.Atom.Test.NotEqual", &Ring1_Atom_Test_notEqual)) {
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
  if (Ring1_Atom_runAll()) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
