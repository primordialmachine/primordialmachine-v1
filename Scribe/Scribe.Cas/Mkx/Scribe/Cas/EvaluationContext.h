// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/EvaluationContext.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#pragma once


#include "Mkx/Scribe/Common.h"
typedef struct Mkx_Scribe_Cas_Node Mkx_Scribe_Cas_Node; // Forward declaration.


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_EvaluationContext)

struct Mkx_Scribe_Cas_EvaluationContext_Class {
  Machine_Object_Class parent;
};

/// An evaluation context is the single communication facility between evaluated nodes and the evaluation visitor.
struct Mkx_Scribe_Cas_EvaluationContext {
  Machine_Object _parent;
};

void
Mkx_Scribe_Cas_EvaluationContext_construct
  (
    Mkx_Scribe_Cas_EvaluationContext *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create an evaluation context.
/// @return The evaluation context.
Mkx_Scribe_Cas_EvaluationContext*
Mkx_Scribe_Cas_EvaluationContext_create
  (
  );