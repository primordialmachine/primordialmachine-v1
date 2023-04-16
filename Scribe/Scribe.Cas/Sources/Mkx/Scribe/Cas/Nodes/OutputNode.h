// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Nodes/BinaryPlusNode.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#pragma once


#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_OutputNode)

struct Mkx_Scribe_Cas_OutputNode_Class {
  Mkx_Scribe_Cas_Node_Class _parent;
};

struct Mkx_Scribe_Cas_OutputNode {
  Mkx_Scribe_Cas_Node _parent;
  Ring2_String* string;
};

void
Mkx_Scribe_Cas_OutputNode_construct
  (
    Mkx_Scribe_Cas_OutputNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Mkx_Scribe_Cas_OutputNode*
Mkx_Scribe_Cas_OutputNode_create
  (
    Ring2_String* string
  );
