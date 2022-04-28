/// @file Runtime/StaticVariablesModule.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/StaticVariablesModule.h"

#include "Ring1/Status.h"

typedef struct Node Node;

struct Node {
  Node* next;
  Machine_UninitializeStaticVariablesCallback* callback;
};

static Node* g_nodes = NULL;

bool Machine_registerStaticVariables(Machine_UninitializeStaticVariablesCallback* callback) {
  if (!callback) {
    return false;
  }
  Node* node = NULL;
  if (Ring1_Memory_allocate(&node, sizeof(Node))) {
    Ring1_Status_set(Ring1_Status_Success);
    return false;
  }
  node->next = g_nodes;
  g_nodes = node;
  node->callback = callback;
  return true;
}

Ring1_Result Machine_initializeStaticVariablesModule() {
  return Ring1_Result_Success;
}

void Machine_uninitializeStaticVariablesModule() {
  while (g_nodes) {
    Node* node = g_nodes;
    g_nodes = node->next;
    Ring1_Memory_deallocate(node);
  }
}

void Machine_notifyStaticVariablesUninitialize() {
  Node* node = g_nodes;
  while (node) {
    node->callback();
    node = node->next;
  }
}
