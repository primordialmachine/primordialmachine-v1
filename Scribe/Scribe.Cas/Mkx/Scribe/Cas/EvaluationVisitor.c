// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/EvaluationVisitor.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Cas/EvaluationVisitor.h"


#include "Mkx/Scribe/Cas/EvaluationContext.h"
#include "Mkx/Scribe/Cas/Nodes.h"


static void
Mkx_Scribe_Cas_EvaluationVisitor_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_EvaluationVisitor* self
  );

static void
Mkx_Scribe_Cas_EvaluationVisitor_constructClass
  (
    Mkx_Scribe_Cas_EvaluationVisitor_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_EvaluationVisitor, Machine_Object,
                         Mkx_Scribe_Cas_EvaluationVisitor_visit,
                         Mkx_Scribe_Cas_EvaluationVisitor_construct,
                         NULL, Mkx_Scribe_Cas_EvaluationVisitor_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_EvaluationVisitor_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_EvaluationVisitor *self
  )
{
  if (self->stack)
  {
    Ring2_Gc_visit(gc, self->stack);
  }
  if (self->context)
  {
    Ring2_Gc_visit(gc, self->context);
  }
}

static void
Mkx_Scribe_Cas_EvaluationVisitor_constructClass
  (
    Mkx_Scribe_Cas_EvaluationVisitor_Class* self
  )
{ }

void
Mkx_Scribe_Cas_EvaluationVisitor_construct
  (
    Mkx_Scribe_Cas_EvaluationVisitor *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);

  self->stack = Ring1_cast(Ring2_Collections_Stack *, Ring2_Collections_ArrayStack_create(Ring2_Context_get()));
  self->context = Mkx_Scribe_Cas_EvaluationContext_create();

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Mkx_Scribe_Cas_EvaluationVisitor_getType());
}

Mkx_Scribe_Cas_EvaluationVisitor*
Mkx_Scribe_Cas_EvaluationVisitor_create
  (
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_EvaluationVisitor_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Mkx_Scribe_Cas_EvaluationVisitor *self = Ring1_cast(Mkx_Scribe_Cas_EvaluationVisitor*,
                                                      Machine_allocateClassObject(ty,
                                                                                  NUMBER_OF_ARGUMENTS,
                                                                                  ARGUMENTS));
  return self;
}

/// @brief Short-code function to get if a stack is empty.
static inline bool
isEmpty
  (
    Ring2_Collections_Stack* stack
  )
{ return Ring2_Collections_Collection_isEmpty(Ring1_cast(Ring2_Collections_Collection *, stack)); }

/// @brief Short-code function to pop a node.
static inline Mkx_Scribe_Cas_Node *
popNode
  (
    Ring2_Collections_Stack* stack
  )
{
  Ring2_Value value = Ring2_Collections_Stack_pop(stack);
  Mkx_Scribe_Cas_Node* node = Ring1_cast(Mkx_Scribe_Cas_Node*, Ring2_Value_getObject(&value));
  return node;
}

/// @brief Short-code function to push a node.
static inline void
pushNode
  (
    Ring2_Collections_Stack* stack,
    Mkx_Scribe_Cas_Node* node
  )
{
  Ring2_Value value;
  Ring2_Value_setObject(&value, Ring1_cast(Machine_Object *, node));
  Ring2_Collections_Stack_push(stack, value);
}

/// Recursively traverses the tree and pushes the nodes on the stack for post-order traversal.
//     ( )|1
//      |
//     ( )|2
//      |
//      +|3
//     / \
//   0|4  1|5
// push(1)
// push(2)
// push(3)
// push(5)
// push(4)
// [1,2,3,5,4]
// So if you pop the nodes from the stack now, you receive
// [4,5,3,2,1]
Mkx_Scribe_Cas_Node*
Mkx_Scribe_Cas_EvaluationVisitor_evaluatePostOrderRecursive
  (
    Mkx_Scribe_Cas_EvaluationVisitor* self,
    Mkx_Scribe_Cas_Node* node
  )
{ 
Evaluate:
  pushNode(self->stack, node);
  int64_t numberOfChildren = Mkx_Scribe_Cas_Node_getNumberOfChildren(node);
  for (int64_t i = 0, n = numberOfChildren; i < n; ++i)
  {
    Mkx_Scribe_Cas_Node* childNode = Mkx_Scribe_Cas_Node_getChildAt(node, i);
    pushNode(self->stack, Mkx_Scribe_Cas_EvaluationVisitor_evaluatePostOrderRecursive(self, childNode));
  }
  /// The node followed its n children from left to right are on the stack.
  for (int64_t i = numberOfChildren; i > 0; --i)
  {
    Mkx_Scribe_Cas_Node* childNode = popNode(self->stack);
    Mkx_Scribe_Cas_Node_setChildAt(node, i - 1, childNode);
  }
  node = popNode(self->stack);
  Mkx_Scribe_Cas_Node *evaluatedNode = Mkx_Scribe_Cas_Node_evaluate(node, self->context);
  if (evaluatedNode != node)
  {
    // A new node was returned.
    // We evaluate that node again.
    node = evaluatedNode;
    goto Evaluate;
  }
  return node;
}

Mkx_Scribe_Cas_Node *
Mkx_Scribe_Cas_EvaluationVisitor_evaluate
  (
    Mkx_Scribe_Cas_EvaluationVisitor* self,
    Mkx_Scribe_Cas_Node* node
  )
{ return Mkx_Scribe_Cas_EvaluationVisitor_evaluatePostOrderRecursive(self, node); }
