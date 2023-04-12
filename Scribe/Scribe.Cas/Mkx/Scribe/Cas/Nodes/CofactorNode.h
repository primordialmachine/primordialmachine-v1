// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/CofactorNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_CofactorNode)

struct Mkx_Scribe_Cas_CofactorNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_CofactorNode {
  Mkx_Scribe_Cas_Node _parent;
  int64_t rowIndex;
  int64_t columnIndex;
  Mkx_Scribe_Cas_Node* operand;
};

void
Mkx_Scribe_Cas_CofactorNode_construct
  (
    Mkx_Scribe_Cas_CofactorNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Scribe_Cas_CofactorNode*
Mkx_Scribe_Cas_CofactorNode_create
  (
    int64_t rowIndex,
    int64_t columnIndex,
    Mkx_Scribe_Cas_Node* operand
  );
