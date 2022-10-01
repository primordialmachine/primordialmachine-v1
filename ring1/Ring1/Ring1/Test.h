// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Test.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_TEST_H_INCLUDED)
#define RING1_TEST_H_INCLUDED

#include <stdbool.h>
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

/// @public
typedef struct Ring1_Test_Context Ring1_Test_Context;

/// @public
typedef void(Ring1_Test_Function)(Ring1_Test_Context* ctx);

/// @public
/// @brief Create a test context.
/// @param ctx A pointer to a Ring1_Test_Context * variable.
/// If this function succeeds, that variable is assigned a pointer to the created Ring1_Test_Context object.
/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
Ring1_CheckReturn() Ring1_Result
Ring1_Test_Context_create
  (
    Ring1_Test_Context **ctx
  );

/// @public
/// @brief Destroy a test context.
/// @param ctx A pointer to the Ring1_Test_Context object.
void
Ring1_Test_Context_destroy
  (
    Ring1_Test_Context* context
  );

/// @public
/// @brief Execute all tests.
/// @param ctx A pointer to the test context.
/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
Ring1_CheckReturn() Ring1_Result
Ring1_Test_Context_runAllTests
  (
    Ring1_Test_Context *ctx
  );

/// @public
/// @brief Add a test.
/// @param name, function The name and the function of the test.
/// @todo Fail if a test with the same name exists.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
/// @remark The test is in the state RING1_TEST_NODE_FLAG_ISNOTEVALUATED.
Ring1_CheckReturn() Ring1_Result
Ring1_Test_Context_addTest
  (
    Ring1_Test_Context* ctx,
    const char* name,
    Ring1_Test_Function* function
  );

/// @public
/// @brief Remove all tests from a test context.
/// @param ctx A pointer to the test context.
void
Ring1_Test_Context_removeAllTests
  (
    Ring1_Test_Context *ctx
  );

/// @public
void
Ring1_Test_Context_assert
  (
    Ring1_Test_Context* ctx,
    bool success,
    const char* message
  );

/// @public
/// @brief Assert an expression is not null.
/// @param ctx A pointer to the test context.
/// @param x The expression.
#define RING1_TEST_ASSERT_NOTNULL(ctx, x) \
  Ring1_Test_Context_assert(ctx, NULL != (x), "`NULL != " #x "` failed")

/// @public
/// @brief Assert two expressions are not equal.
/// @param ctx A pointer to the test context.
/// @param x, y The expressions.
#define RING1_TEST_ASSERT_NEQ(ctx, x, y) \
  Ring1_Test_Context_assert(ctx, (x) != (y), "`" #x " != " #y "` failed\n");

/// @public
/// @brief Assert two expressions are equal.
/// @param ctx A pointer to the test context.
/// @param x, y The expressions.
#define RING1_TEST_ASSERT_EQ(ctx, x, y) \
  Ring1_Test_Context_assert(ctx, (x) == (y), "`" #x " == " #y "` failed\n");

/// @public
/// @brief Assert an expression is true.
/// @param ctx A pointer to the test context.
/// @param x The expression.
#define RING1_TEST_ASSERT_TRUE(ctx, x) \
  Ring1_Test_Context_assert(ctx, true == (x), "` true == " #x "` failed")

/// @public
/// @brief Assert an expression is false.
/// @param ctx A pointer to the test context.
/// @param x The expression.
#define RING1_TEST_ASSERT_FALSE(ctx, x) \
  Ring1_Test_Context_assert(ctx, false == (x), "` false == " #x "` failed")

#endif // RING1_TEST_H_INCLUDED
