/// @file Ring3/Gdl/Syntactical/Node.h
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_SYNTACTICAL_NODE_H_INCLUDED)
#define RING3_GDL_SYNTACTICAL_NODE_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Syntactical/Node.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/Syntactical/NodeKind.h"
#include "Ring3/Gdl/Literals/BooleanLiteral.h"
#include "Ring3/Gdl/Literals/IntegerLiteral.h"
#include "Ring3/Gdl/Literals/RealLiteral.h"
#include "Ring3/Gdl/Literals/StringLiteral.h"
#include "Ring3/Gdl/Literals/VoidLiteral.h"
#include "Ring3/Gdl/Name.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Node)

struct Machine_Gdl_Node_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gdl_Node {
  Machine_Object __parent;

  /// @brief The parent node of this node if any, null pointer otherwise.
  Machine_Gdl_Node* parent;
  Ring2_Collections_List* children;

  Machine_Gdl_NodeKind kind;
  Ring2_Value value;
};

/// - #Machine_Gdl_NodeKind_Boolean
/// Ring3_Gdl_BooleanLiteral
/// - #Machine_Gdl_NodeKind_Integer
/// Ring3_Gdl_IntegerLiteral
/// - #Machine_Gdl_NodeKind_Real
/// Ring3_Gdl_RealLiteral
/// - #Machine_Gdl_NodeKind_String
/// Ring3_Gdl_StringLiteral
/// - #Machine_Gdl_NodeKind_Void
/// Ring3_Gdl_VoidLiteral
/// - #Machine_Gdl_NodeKind_Name
/// Ring3_Gdl_Name
/// - #Machine_Gdl_NodeKind_CompilationUnit
/// Ring2_String
Ring1_NoDiscardReturn() Machine_Gdl_Node*
Machine_Gdl_Node_create
  (
    Machine_Gdl_NodeKind kind,
    Ring2_Value const* value
  );

/// @brief Append a node to the node list of this node.
/// @param self This node.
/// @param other The node to append.
void
Machine_Gdl_Node_append
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Node* other
  );

/// @brief Prepend a node to the node list of this node.
/// @param self This node.
/// @param other The node to prepend.
void
Machine_Gdl_Node_prepend
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Node* other
  );

/// @brief Insert a node into the node list of this node.
/// @param self This node.
/// @param index The index.
/// @param other The node to insert.
void
Machine_Gdl_Node_insertAt
  (
    Machine_Gdl_Node* self,
    Ring2_Integer index,
    Machine_Gdl_Node* other
  );

/// @brief Get the child node at the specified index in the node list of this node.
/// @param self This node.
/// @param index The index.
/// @return The child node.
Ring1_NoDiscardReturn() Machine_Gdl_Node *
Machine_Gdl_Node_getAt
  (
    Machine_Gdl_Node* self,
    Ring2_Integer index
  );

Ring1_NoDiscardReturn() int64_t
Machine_Gdl_Node_getSize
  (
    Machine_Gdl_Node* self
  );

/// @brief Get the kind of this node.
/// @param self A pointer to this node.
/// @return The kind of this node.
Ring1_NoDiscardReturn() Machine_Gdl_NodeKind
Machine_Gdl_Node_getKind
  (
    Machine_Gdl_Node const *self
  );
  
#endif // RING3_GDL_SYNTACTICAL_NODE_H_INCLUDED
