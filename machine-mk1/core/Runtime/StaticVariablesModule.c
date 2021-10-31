/// @file Runtime/StaticVariablesModule.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/StaticVariablesModule.h"



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
  Node *node = c_alloc(sizeof(Node));
  if (!node) {
    return false;
  }
  node->next = g_nodes; g_nodes = node;
  node->callback = callback;
  return true;
}

Machine_StatusValue Machine_initializeStaticVariablesModule() {
  return Machine_Status_Success;
}

void Machine_uninitializeStaticVariablesModule() {
  while (g_nodes) {
    Node* node = g_nodes; g_nodes = node->next;
    c_dealloc(node);
  }
}

void Machine_notifyStaticVariablesUninitialize() {
  Node* node = g_nodes;
  while (node) {
    node->callback();
    node = node->next;
  }
}
