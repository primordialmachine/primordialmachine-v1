// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/OneNodeNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_OneNode)

struct Mkx_Scribe_Cas_OneNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_OneNode {
  Mkx_Scribe_Cas_Node _parent;
};

void
Mkx_Scribe_Cas_OneNode_construct
  (
    Mkx_Scribe_Cas_OneNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Scribe_Cas_OneNode *
Mkx_Scribe_Cas_OneNode_create
  (
  );
