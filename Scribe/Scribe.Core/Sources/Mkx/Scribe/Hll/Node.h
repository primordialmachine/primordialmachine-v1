// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Hll/Node.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_HLL_NODE_H_INCLUDED)
#define MKX_SCRIBE_HLL_NODE_H_INCLUDED


#include "Mkx/Scribe/Hll/NodeType.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Hll_Node)

struct Mkx_Scribe_Hll_Node_Class {
  Machine_Object_Class _parent;
};

struct Mkx_Scribe_Hll_Node {
  Machine_Object _parent;
  Ring2_Collections_List* children;
  Mkx_Scribe_Position* position;
  Mkx_Scribe_Hll_NodeKind kind;
};

/// @brief Construct a HLL node.
/// @param context The context.
/// @param node The node.
/// @param kind The kind of the node.
/// @param position The position of the node.
void
Mkx_Scribe_Hll_Node_construct
  (
    Mkx_Scribe_Hll_Node *self,
    size_t numberOfArguments,
    Ring2_Value const *argumens
  );

Mkx_Scribe_Hll_Node *
Mkx_Scribe_Hll_Node_create
  (
    Mkx_Scribe_Hll_NodeKind kind,
    Mkx_Scribe_Position* position
  );

/// @brief Get the position of this node.
/// @param context The context.
/// @param self This node.
/// @return The position of this node.
Mkx_Scribe_Position*
Mkx_Scribe_Hll_Node_getPosition
  (
    Mkx_Scribe_Hll_Node *self
  );

/// @brief Get the type of this node.
/// @param context The context.
/// @param self This node.
/// @return The type of this node.
Mkx_Scribe_Hll_NodeKind
Mkx_Scribe_Hll_Node_getKind
  (
    Mkx_Scribe_Hll_Node* self
  );

/// @brief Get the number of child nodes of this node.
/// @param context The context.
/// @param self This node.
/// @return The number of child nodes of this node.
int64_t
Mkx_Scribe_Hll_Node_getNumberOfChildren
  (
    Mkx_Scribe_Hll_Node* self
  );

/// @brief Get the child node of this node at the specified index.
/// @param context The context.
/// @param self This node.
/// @param index The index. Must be within the bounds of zero and the number of child nodes minus 1.
/// @return The child node.
Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_getChildAt
  (
    Mkx_Scribe_Hll_Node* self,
    int64_t index
  );

/// @brief Append a child node to the list of child nodes of this node.
/// @param context The context.
/// @param self This node.
/// @param node The child node.
void
Mkx_Scribe_Hll_Node_append
  (
    Mkx_Scribe_Hll_Node* self,
    Mkx_Scribe_Hll_Node* element
  );

/// @brief Prepend a child node to the list of child nodes of this node.
/// @param context The context.
/// @param self This node.
/// @param node The child node.
void
Mkx_Scribe_Hll_Node_prependChild
  (
    Mkx_Scribe_Hll_Node* self,
    Mkx_Scribe_Hll_Node* node
  );

/// @brief Insert a child node into the list of child nodes of this node.
/// @param context The context.
/// @param self This node.
/// @param index The index of the child. Must be within the bounds of zero and the number of children of this node.
void
Mkx_Scribe_Hll_Node_insertChildAt
  (
    Mkx_Scribe_Hll_Node* self,
    int64_t index,
    Mkx_Scribe_Hll_Node* node
  );

#endif // MKX_SCRIBE_HLL_NODE_H_INCLUDED
