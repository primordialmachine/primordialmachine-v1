// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/BinaryPlusNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_BinaryPlusNode)

struct Mkx_Scribe_Cas_BinaryPlusNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_BinaryPlusNode {
  Mkx_Scribe_Cas_Node _parent;
  Mkx_Scribe_Cas_Node* leftOperand;
  Mkx_Scribe_Cas_Node* rightOperand;
};

void
Mkx_Scribe_Cas_BinaryPlusNode_construct
  (
    Mkx_Scribe_Cas_BinaryPlusNode *self,
    size_t numberOfArguments,
    Ring2_Value const *values
  );

Mkx_Scribe_Cas_BinaryPlusNode *
Mkx_Scribe_Cas_BinaryPlusNode_create
  (
    Mkx_Scribe_Cas_Node *leftOperand,
    Mkx_Scribe_Cas_Node *rightOperand
  );
