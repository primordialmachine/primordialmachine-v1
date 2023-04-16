// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/Index1dNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_Index1dNode)

struct Mkx_Scribe_Cas_Index1dNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_Index1dNode {
  Mkx_Scribe_Cas_Node _parent;
  int64_t index;
  Mkx_Scribe_Cas_Node* operand;
};

void
Mkx_Scribe_Cas_Index1dNode_construct
  (
    Mkx_Scribe_Cas_Index1dNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Scribe_Cas_Index1dNode*
Mkx_Scribe_Cas_Index1dNode_create
  (
    int64_t index,
    Mkx_Scribe_Cas_Node* operand
  );
