#pragma once

#include "Ring1/Status.h"
#include "Ring2/_Include.h"
#include <stdio.h>

/// @brief
/// - Create an interpreter context.
///   If creation fails, the test fails.
/// - Invoke the function with the context.
///   If
///   - the function is a null pointer or
///   - the function raises an error
///   the test fails.
///   If the test fails goto (a).
/// - Destroys the interpreter context (a).
/// - Returns the result of the test.
int
Mkx_Test_execute
  (
    Ring2_ForeignProcedure *testFunction
  );

#define MKX_TEST_ASSERT_NEQ(context, x, y) \
  if (!((x) != (y))) { \
    fprintf(stderr, #x " != " #y " failed\n"); \
    Ring1_Status_set(Ring1_Status_TestFailed); \
    Ring2_jump(); \
  }

#define MKX_TEST_ASSERT_EQ(context, x, y) \
  if (!((x) == (y))) { \
    fprintf(stderr, #x " == " #y " failed\n"); \
    Ring1_Status_set(Ring1_Status_TestFailed); \
    Ring2_jump(); \
  }

typedef struct StringFixture
{
  const char* bytes;
  const size_t numberOfBytes;
} StringFixture;
