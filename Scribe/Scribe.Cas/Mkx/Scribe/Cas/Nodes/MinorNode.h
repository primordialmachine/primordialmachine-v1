// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/MinorNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_MinorNode)

struct Mkx_Scribe_Cas_MinorNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_MinorNode {
  Mkx_Scribe_Cas_Node _parent;
  int64_t rowIndex;
  int64_t columnIndex;
  Mkx_Scribe_Cas_Node* operand;
};

void
Mkx_Scribe_Cas_MinorNode_construct
  (
    Mkx_Scribe_Cas_MinorNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief The minor
Mkx_Scribe_Cas_MinorNode*
Mkx_Scribe_Cas_MinorNode_create
  (
    int64_t rowIndex,
    int64_t columnIndex,
    Mkx_Scribe_Cas_Node* operand
  );
