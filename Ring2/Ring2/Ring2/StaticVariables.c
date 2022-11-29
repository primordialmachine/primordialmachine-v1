/// @file Ring2/StaticVariables.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/StaticVariables.h"
#undef RING2_PRIVATE


#include "Ring1/Memory.h"
#include "Ring1/Status.h"
#include <stddef.h>


typedef struct Node Node;

struct Node {
  Node* next;
  Ring2_UninitializeStaticVariablesCallback* callback;
};

static Node* g_nodes = NULL;

Ring1_CheckReturn() Ring1_Result
Ring2_registerStaticVariables
  (
    Ring2_UninitializeStaticVariablesCallback* callback
  )
{
  if (!callback) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Node* node = NULL;
  if (Ring1_Memory_allocate(&node, sizeof(Node))) {
    return Ring1_Result_Failure;
  }
  node->next = g_nodes;
  g_nodes = node;
  node->callback = callback;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring2_initializeStaticVariablesModule
  (
  )
{ return Ring1_Result_Success; }

void
Ring2_uninitializeStaticVariablesModule
  (
  )
{
  while (g_nodes) {
    Node* node = g_nodes;
    g_nodes = node->next;
    Ring1_Memory_deallocate(node);
  }
}

Ring1_Module_Define(Ring2, StaticVariablesModule, Ring2_initializeStaticVariablesModule, Ring2_uninitializeStaticVariablesModule)

void
Ring2_notifyStaticVariablesUninitialize
  (
  )
{
  Node* node = g_nodes;
  while (node) {
    node->callback();
    node = node->next;
  }
}
