// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/DeleteRowNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_DeleteRowNode)

struct Mkx_Scribe_Cas_DeleteRowNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_DeleteRowNode {
  Mkx_Scribe_Cas_Node _parent;
  int64_t rowIndex;
  Mkx_Scribe_Cas_Node* operand;
};

void
Mkx_Scribe_Cas_DeleteRowNode_construct
  (
    Mkx_Scribe_Cas_DeleteRowNode *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Scribe_Cas_DeleteRowNode*
Mkx_Scribe_Cas_DeleteRowNode_create
  (
    int64_t rowIndex,
    Mkx_Scribe_Cas_Node* operand
  );
