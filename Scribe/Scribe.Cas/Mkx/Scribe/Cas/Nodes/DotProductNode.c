/// @file Mkx/Scribe/Cas/Nodes/DotProductNode.h
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/DotProductNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_DotProductNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_DotProductNode* self
  );

static void
Mkx_Scribe_Cas_DotProductNode_constructClass
  (
    Mkx_Scribe_Cas_DotProductNode_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_DotProductNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_DotProductNode_visit,
                         &Mkx_Scribe_Cas_DotProductNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_DotProductNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_DotProductNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_DotProductNode* self
  )
{
  if (self->leftOperand) {
    Ring2_Gc_visit(gc, self->leftOperand);
  }
  if (self->rightOperand) {
    Ring2_Gc_visit(gc, self->rightOperand);
  }
}

static void
check
  (
    Mkx_Scribe_Cas_Node* node
  )
{
  if (!node)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_DotProduct != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_DotProductNode* dotProductNode = Ring1_cast(Mkx_Scribe_Cas_DotProductNode*, node);
  if (!dotProductNode->leftOperand || !dotProductNode->rightOperand)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_DotProductNode*
clone
  (
    Mkx_Scribe_Cas_DotProductNode* self
  )
{
  return Mkx_Scribe_Cas_DotProductNode_create(self->leftOperand ? Mkx_Scribe_Cas_Node_clone(self->leftOperand) : NULL,
                                              self->rightOperand ? Mkx_Scribe_Cas_Node_clone(self->rightOperand) : NULL);
}

static void
emit
  (
    Mkx_Scribe_Cas_DotProductNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->leftOperand);
  Ring2_String* starString = Ring2_String_fromC(false, " . ");
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(starString)));
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->rightOperand);
}

static Mkx_Scribe_Cas_Node*
evaluateVectorVector
  (
    Mkx_Scribe_Cas_VectorNode* leftOperand,
    Mkx_Scribe_Cas_VectorNode* rightOperand,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  // Vectors must have the same number of elements.
  if (Mkx_Scribe_Cas_VectorNode_getNumberOfElements(leftOperand) != Mkx_Scribe_Cas_VectorNode_getNumberOfElements(rightOperand))
  {
    Ring1_Log_error("%s:%d: operand vectors must be of the same dimensionality\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }

  int64_t l = Mkx_Scribe_Cas_VectorNode_getNumberOfElements(leftOperand);
   
  Mkx_Scribe_Cas_Node* e = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
  for (int64_t i = 0; i < l; ++i)
  {
      Mkx_Scribe_Cas_Node* e1 = Mkx_Scribe_Cas_VectorNode_getElement(leftOperand, i),
                         * e2 = Mkx_Scribe_Cas_VectorNode_getElement(rightOperand, i);
      Mkx_Scribe_Cas_Node* e3 = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(e1, e2));
      e = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryPlusNode_create(e, e3));
  }
  return Ring1_cast(Mkx_Scribe_Cas_Node*, e);
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_DotProductNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  static const bool OPTIMIZE = true;

  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  if (Mkx_Scribe_Cas_NodeKind_Vector == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
      Mkx_Scribe_Cas_NodeKind_Vector == Mkx_Scribe_Cas_Node_getKind(self->rightOperand))
  {
    return evaluateVectorVector(Ring1_cast(Mkx_Scribe_Cas_VectorNode*, self->leftOperand),
                                Ring1_cast(Mkx_Scribe_Cas_VectorNode*, self->rightOperand),
                                evaluationContext);
  }
  return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_DotProductNode* self
  )
{ return 2; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_DotProductNode* self,
    int64_t index
  )
{
  switch (index)
  {
  case 0:
    return self->leftOperand;
  case 1:
    return self->rightOperand;
  default:
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  };
}

static void
setChildAt
  (
    Mkx_Scribe_Cas_DotProductNode* self,
    int64_t index,
    Mkx_Scribe_Cas_Node* node
  )
{
  switch (index)
  {
  case 0:
  { self->leftOperand = node; }
  break;
  case 1:
  {self->rightOperand = node; }
  break;
  default:
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  };
}

void
Mkx_Scribe_Cas_DotProductNode_construct
  (
    Mkx_Scribe_Cas_DotProductNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_DotProduct;
  self->leftOperand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[0]));
  self->rightOperand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[1]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_DotProductNode_getType());
}

Mkx_Scribe_Cas_DotProductNode*
Mkx_Scribe_Cas_DotProductNode_create
  (
    Mkx_Scribe_Cas_Node* leftOperand,
    Mkx_Scribe_Cas_Node* rightOperand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_DotProductNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,leftOperand));
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,rightOperand));
  Mkx_Scribe_Cas_DotProductNode* self = Ring1_cast(Mkx_Scribe_Cas_DotProductNode*,
                                                   Machine_allocateClassObject(ty,
                                                                               NUMBER_OF_ARGUMENTS,
                                                                               arguments));
  return self;
}

static void
Mkx_Scribe_Cas_DotProductNode_constructClass
  (
    Mkx_Scribe_Cas_DotProductNode_Class* self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t(*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
