// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Test.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Test.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Ring1/Status.h"

#define RING1_TEST_PRIVATE (1)
#include "Ring1/Test/Node.h"
#include "Ring1/Test/Context.h"
#undef RING1_TEST_PRIVATE

/// @internal.
/// @brief Initialize a test context.
/// @param ctx A pointer to the uninitialized test context.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
Ring1_CheckReturn() Ring1_Result
Ring1_Test_Context_initialize
  (
    Ring1_Test_Context* ctx
  );

/// @internal.
/// @brief Uninitialize a test context.
/// @param ctx A pointer to the initialized test context.
void
Ring1_Test_Context_uninitialize
  (
    Ring1_Test_Context* ctx
  );


Ring1_CheckReturn() Ring1_Result
Ring1_Test_Context_initialize
  (
    Ring1_Test_Context* ctx
  )
{
  if (!ctx) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  ctx->nodes = NULL;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Test_Context_addTest
  (
    Ring1_Test_Context* ctx,
    const char* name,
    Ring1_Test_Function* function
  )
{
  Ring1_Test_Node* node;
  if (Ring1_Test_Node_create(&node, name, function))
  { return Ring1_Result_Failure; }
  node->next = ctx->nodes;
  ctx->nodes = node;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Test_Context_create
  ( 
    Ring1_Test_Context** ctx
  )
{
  Ring1_Test_Context *o = malloc(sizeof(Ring1_Test_Context));
  if (!o) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_initialize(o)) {
    free(o);
    return Ring1_Result_Failure;
  }
  *ctx = o;
  return Ring1_Result_Success;
}

void
Ring1_Test_Context_destroy
  (
    Ring1_Test_Context* ctx
  )
{
  Ring1_Test_Context_uninitialize(ctx);
  free(ctx);
}

void
Ring1_Test_Context_uninitialize
  (
    Ring1_Test_Context* ctx
  )
{
  Ring1_Test_Context_removeAllTests(ctx);
}

void
Ring1_Test_Context_removeAllTests
  (
    Ring1_Test_Context* ctx
  )
{
  while (ctx->nodes)
  {
    Ring1_Test_Node* node = ctx->nodes;
    ctx->nodes = node->next;
    Ring1_Test_Node_destroy(node);
  }
}

Ring1_CheckReturn() Ring1_Result
Ring1_Test_Context_runAllTests
  (
    Ring1_Test_Context *ctx
  )
{
  int total = 0, succeeded = 0, failed = 0;
  for (Ring1_Test_Node* node = ctx->nodes; NULL != node; node = node->next) {
    ctx->currentNode = node;
    node->flags = RING1_TEST_NODE_FLAG_ISEVALUATING;
    node->function(ctx);
    node->flags = (node->flags & ~RING1_TEST_NODE_FLAG_ISEVALUATING) | RING1_TEST_NODE_FLAG_ISEVALUATED;
    if (0 == (node->flags & RING1_TEST_NODE_FLAG_HASERRORS))
    {
      fprintf(stdout, "%s succeeded\n", node->name);
      total++;
      succeeded++;
    }
    else
    {
      fprintf(stdout, "%s failed\n", node->name);
      total++;
      failed++;
    }
  }
  fprintf(stdout, "%d/%d succeeded\n", succeeded, total);
  return Ring1_Result_Success;
}

void
Ring1_Test_Context_assert
  (
    Ring1_Test_Context* ctx,
    bool success,
    const char* message
  )
{
  if (!success)
  {
    ctx->currentNode->flags |= RING1_TEST_NODE_FLAG_HASERRORS;
    fprintf(stderr, "%s", message);
  }
}
