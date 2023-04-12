// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/Node.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Cas/Node.h"


MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_Node,
                         Mkx_Scribe_Node,
                         NULL,
                         &Mkx_Scribe_Cas_Node_construct,
                         NULL,
                         NULL,
                         NULL);

void
Mkx_Scribe_Cas_Node_construct
  (
    Mkx_Scribe_Cas_Node* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Node_construct(Ring1_cast(Mkx_Scribe_Node*, self), numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_Node_getType());
}

Mkx_Scribe_Cas_NodeKind
Mkx_Scribe_Cas_Node_getKind
  (
    Mkx_Scribe_Cas_Node* self
  )
{ return self->kind; }

void
Mkx_Scribe_Cas_Node_emit
  (
    Mkx_Scribe_Cas_Node* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Scribe_Cas_Node, emit, , self, emissionContext); }

Mkx_Scribe_Cas_Node *
Mkx_Scribe_Cas_Node_clone
  (
    Mkx_Scribe_Cas_Node* self
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Scribe_Cas_Node, clone, return, self); }

Mkx_Scribe_Cas_Node*
Mkx_Scribe_Cas_Node_evaluate
  (
    Mkx_Scribe_Cas_Node* self,
    Mkx_Scribe_Cas_EvaluationContext *evaluationContext
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Scribe_Cas_Node, evaluate, return , self, evaluationContext); }

int64_t
Mkx_Scribe_Cas_Node_getNumberOfChildren
  (
    Mkx_Scribe_Cas_Node* self
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Scribe_Cas_Node, getNumberOfChildren, return , self); }

Mkx_Scribe_Cas_Node*
Mkx_Scribe_Cas_Node_getChildAt
  (
    Mkx_Scribe_Cas_Node* self,
    int64_t index
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Scribe_Cas_Node, getChildAt, return , self, index); }

void
Mkx_Scribe_Cas_Node_setChildAt
  (
    Mkx_Scribe_Cas_Node* self,
    int64_t index,
    Mkx_Scribe_Cas_Node* node
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Scribe_Cas_Node, setChildAt, , self, index, node); }
