// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Test/Node.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_TEST_PRIVATE (1)
#include "Ring1/Test/Node.h"
#undef RING1_TEST_PRIVATE

#include "Ring1/Status.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

Ring1_CheckReturn() Ring1_Result
Ring1_Test_Node_create
  (
    Ring1_Test_Node** node,
    const char* name,
    Ring1_Test_Function* function
  )
{
  Ring1_Test_Node* o = malloc(sizeof(Ring1_Test_Node));
  if (!o) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  o->flags = RING1_TEST_NODE_FLAG_ISNOTEVALUATED;
  o->name = _strdup(name);
  if (!o->name) {
    free(o);
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  o->function = function;
  o->next = NULL;
  *node = o;
  return Ring1_Result_Success;
}

void
Ring1_Test_Node_destroy
  (
    Ring1_Test_Node* node
  )
{
  free(node->name);
  free(node);
}
