// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Node.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_CAS_NODE_H)
#define MKX_SCRIBE_CAS_NODE_H


#include "Mkx/Scribe/Common.h"
#include "Mkx/Scribe/Cas/NodeKind.h"
typedef struct Mkx_Scribe_Cas_EmissionContext Mkx_Scribe_Cas_EmissionContext; // Forward declaration.
typedef struct Mkx_Scribe_Cas_EvaluationContext Mkx_Scribe_Cas_EvaluationContext; // Forward declaration.


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_Node)

struct Mkx_Scribe_Cas_Node_Class {
  Mkx_Scribe_Node_Class _parent;

  Mkx_Scribe_Cas_Node* (*clone)(Mkx_Scribe_Cas_Node* self);
  Mkx_Scribe_Cas_Node *(*evaluate)(Mkx_Scribe_Cas_Node* self, Mkx_Scribe_Cas_EvaluationContext *evaluationContext);
  void (*emit)(Mkx_Scribe_Cas_Node* self, Mkx_Scribe_Cas_EmissionContext* emissionContext);
  int64_t (*getNumberOfChildren)(Mkx_Scribe_Cas_Node* self);
  Mkx_Scribe_Cas_Node *(*getChildAt)(Mkx_Scribe_Cas_Node* self, int64_t index);
  void (*setChildAt)(Mkx_Scribe_Cas_Node* self, int64_t index, Mkx_Scribe_Cas_Node* node);
};

struct Mkx_Scribe_Cas_Node {
  Mkx_Scribe_Node _parent;
  
  /// @brief The kind of this node.
  Mkx_Scribe_Cas_NodeKind kind;
};

void
Mkx_Scribe_Cas_Node_construct
  (
    Mkx_Scribe_Cas_Node* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Scribe_Cas_NodeKind
Mkx_Scribe_Cas_Node_getKind
  (
    Mkx_Scribe_Cas_Node* self
  );

/// @brief Get the number of child nodes of this node.
/// @param context The context.
/// @param self This node.
/// @return The number of child nodes of this node.
int64_t
Mkx_Scribe_Cas_Node_getNumberOfChildren
  (
    Mkx_Scribe_Cas_Node* self
  );

/// @brief Get a child node of this node.
/// @param context The context.
/// @param self This node.
/// @param index The index of the child. Must be within the bounds of zero and the number of children of this node minus 1.
/// @return The child node.
Mkx_Scribe_Cas_Node*
Mkx_Scribe_Cas_Node_getChildAt
  (
    Mkx_Scribe_Cas_Node* self,
    int64_t index
  );

void
Mkx_Scribe_Cas_Node_setChildAt
  (
    Mkx_Scribe_Cas_Node* self,
    int64_t index,
    Mkx_Scribe_Cas_Node *node
  );

Mkx_Scribe_Cas_Node*
Mkx_Scribe_Cas_Node_evaluate
  (
    Mkx_Scribe_Cas_Node* self,
    Mkx_Scribe_Cas_EvaluationContext *evaluationContext
  );

void
Mkx_Scribe_Cas_Node_emit
  (
    Mkx_Scribe_Cas_Node* self,
    Mkx_Scribe_Cas_EmissionContext *emissionContext
  );

Mkx_Scribe_Cas_Node *
Mkx_Scribe_Cas_Node_clone
  (
    Mkx_Scribe_Cas_Node *self
  );

#endif // MKX_SCRIBE_CAS_NODE_H
