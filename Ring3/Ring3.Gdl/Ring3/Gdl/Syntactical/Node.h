/// @file Ring3/Gdl/Syntactical/Node.h
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_SYNTACTICAL_NODE_H_INCLUDED)
#define RING3_GDL_SYNTACTICAL_NODE_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Syntactical/Node.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/Syntactical/NodeKind.h"

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
  Ring2_String* text;
};

Machine_Gdl_Node*
Machine_Gdl_Node_create
  (
    Machine_Gdl_NodeKind kind,
    Ring2_String* text
  );

#endif // RING3_GDL_SYNTACTICAL_NODE_H_INCLUDED
