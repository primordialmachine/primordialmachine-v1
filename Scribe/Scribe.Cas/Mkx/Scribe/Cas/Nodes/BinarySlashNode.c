/// @file Mkx/Scribe/Cas/Nodes/BinarySlashNode.c
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/BinarySlashNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_BinarySlashNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_BinarySlashNode *self
  );

static void
Mkx_Scribe_Cas_BinarySlashNode_constructClass
  (
    Mkx_Scribe_Cas_BinarySlashNode_Class *self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_BinarySlashNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_BinarySlashNode_visit,
                         &Mkx_Scribe_Cas_BinarySlashNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_BinarySlashNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_BinarySlashNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_BinarySlashNode* self
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
  if (Mkx_Scribe_Cas_NodeKind_BinarySlash != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_BinarySlashNode* binarySlashNode = Ring1_cast(Mkx_Scribe_Cas_BinarySlashNode*, node);
  if (!binarySlashNode->leftOperand || !binarySlashNode->rightOperand)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_BinarySlashNode*
clone
  (
    Mkx_Scribe_Cas_BinarySlashNode* self
  )
{
  return Mkx_Scribe_Cas_BinarySlashNode_create(self->leftOperand ? Mkx_Scribe_Cas_Node_clone(self->leftOperand) : NULL,
                                               self->rightOperand ? Mkx_Scribe_Cas_Node_clone(self->rightOperand) : NULL);
}

static void
emit
  (
    Mkx_Scribe_Cas_BinarySlashNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->leftOperand);
  Ring2_String* slashString = Ring2_String_fromC(false, " / ");
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(slashString)));
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
  int64_t n = Mkx_Scribe_Cas_VectorNode_getNumberOfElements(leftOperand);

  Mkx_Scribe_Cas_VectorNode* result = Mkx_Scribe_Cas_VectorNode_create(n);

  for (int64_t i = 0; i < n; ++i)
  {
    Mkx_Scribe_Cas_Node* e1 = Mkx_Scribe_Cas_VectorNode_getElement(leftOperand, i);
    Mkx_Scribe_Cas_Node* e2 = Mkx_Scribe_Cas_VectorNode_getElement(rightOperand, i);
    e1 = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_GroupNode_create(e1));
    e2 = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_GroupNode_create(e2));
    Mkx_Scribe_Cas_Node* e = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinarySlashNode_create(e1, e2));
    Mkx_Scribe_Cas_VectorNode_setElement(result, i, e);
  }

  return Ring1_cast(Mkx_Scribe_Cas_Node*, result);
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_BinarySlashNode* self,
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

  if (OPTIMIZE)
  {
    return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
  }
  else
  {
    return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
  }
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_BinarySlashNode* self
  )
{ return 2; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_BinarySlashNode* self,
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
    Mkx_Scribe_Cas_BinarySlashNode* self,
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
Mkx_Scribe_Cas_BinarySlashNode_construct
  (
    Mkx_Scribe_Cas_BinarySlashNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_BinarySlash;
  self->leftOperand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[0]));
  self->rightOperand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[1]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_BinarySlashNode_getType());
}

Mkx_Scribe_Cas_BinarySlashNode*
Mkx_Scribe_Cas_BinarySlashNode_create
  (
    Mkx_Scribe_Cas_Node* leftOperand,
    Mkx_Scribe_Cas_Node* rightOperand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_BinarySlashNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,leftOperand));
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,rightOperand));
  Mkx_Scribe_Cas_BinarySlashNode* self = Ring1_cast(Mkx_Scribe_Cas_BinarySlashNode*,
                                                    Machine_allocateClassObject(ty,
                                                                                NUMBER_OF_ARGUMENTS,
                                                                                arguments));
  return self;
}

static void
Mkx_Scribe_Cas_BinarySlashNode_constructClass
  (
    Mkx_Scribe_Cas_BinarySlashNode_Class *self
  )
{ 
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext *)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t(*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
