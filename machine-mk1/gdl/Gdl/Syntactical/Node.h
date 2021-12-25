/// @file Gdl/Syntactical/Node.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GDL_SYNTACTICAL_NODE_H_INCLUDED)
#define MACHINE_GDL_SYNTACTICAL_NODE_H_INCLUDED

#include "Gdl/Context.h"
#include "Gdl/Syntactical/NodeKind.h"
#include "_Collections.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Gdl_Node)

struct Machine_Gdl_Node_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gdl_Node {
  Machine_Object __parent;

  /// @brief The parent node of this node if any, null pointer otherwise.
  Machine_Gdl_Node* parent;
  Machine_List* children;

  Machine_Gdl_NodeKind kind;
  Machine_String* text;
};

Machine_Gdl_Node* Machine_Gdl_Node_create(Machine_Gdl_NodeKind kind, Machine_String* text);

#endif // MACHINE_GDL_SYNTACTICAL_NODE_H_INCLUDED
