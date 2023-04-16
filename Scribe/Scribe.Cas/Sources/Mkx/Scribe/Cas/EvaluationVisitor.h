// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/EvaluationVisitor.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_CAS_EVALUATIONVISITOR_H_INCLUDED)
#define MKX_SCRIBE_CAS_EVALUATIONVISITOR_H_INCLUDED


#include "Mkx/Scribe/Common.h"
typedef struct Mkx_Scribe_Cas_Node Mkx_Scribe_Cas_Node; // Forward declaration.
typedef struct Mkx_Scribe_Cas_EvaluationContext Mkx_Scribe_Cas_EvaluationContext; // Forward declaration.

MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Cas_EvaluationVisitor)

struct Mkx_Scribe_Cas_EvaluationVisitor_Class {
  Machine_Object_Class _parent;
};

/// Take an "add" expression as an example:
/// EXP:=(a + 0) * (0 + b).
/// We push (a + 0) on the evaluation stack and evaluate (a + 0).
/// The evaluation yields (a).
/// We replace (a + 0) by (a) in EXP. 
struct Mkx_Scribe_Cas_EvaluationVisitor {
  Machine_Object _parent;
  /// @brief The evaluation context.
  Mkx_Scribe_Cas_EvaluationContext* context;
  /// @brief The visitation stack to perform post-order traversal.
  Ring2_Collections_Stack* stack;
};

void
Mkx_Scribe_Cas_EvaluationVisitor_construct
  (
    Mkx_Scribe_Cas_EvaluationVisitor* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create an evaluation visitor.
/// @return The evaluation visitor.
Mkx_Scribe_Cas_EvaluationVisitor *
Mkx_Scribe_Cas_EvaluationVisitor_create
  (
  );
  
Mkx_Scribe_Cas_Node *
Mkx_Scribe_Cas_EvaluationVisitor_evaluate
  (
    Mkx_Scribe_Cas_EvaluationVisitor* self,
    Mkx_Scribe_Cas_Node* node
  );

#endif // MKX_SCRIBE_CAS_EVALUATIONSTACK_H_INCLUDED
