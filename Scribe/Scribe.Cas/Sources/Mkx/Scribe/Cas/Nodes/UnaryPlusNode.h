// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/UnaryPlusNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_UnaryPlusNode)

struct Mkx_Scribe_Cas_UnaryPlusNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_UnaryPlusNode {
  Mkx_Scribe_Cas_Node _parent;
  Mkx_Scribe_Cas_Node* operand;
};

void
Mkx_Scribe_Cas_UnaryPlusNode_construct
  (
    Mkx_Scribe_Cas_UnaryPlusNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Scribe_Cas_UnaryPlusNode *
Mkx_Scribe_Cas_UnaryPlusNode_create
  (
    Mkx_Scribe_Cas_Node *operand
  );
