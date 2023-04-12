// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/VariableNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_VariableNode)

struct Mkx_Scribe_Cas_VariableNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_VariableNode {
  Mkx_Scribe_Cas_Node _parent;
  Ring2_String* displayName;
};

/// @brief Construct a variable node.
/// @param context The context.
/// @param self The "variable" node.
/// @param displayName The display name of the variable.
void
Mkx_Scribe_Cas_VariableNode_construct
  (
    Mkx_Scribe_Cas_VariableNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Scribe_Cas_VariableNode *
Mkx_Scribe_Cas_VariableNode_create
  (
    Ring2_String* displayName
  );
