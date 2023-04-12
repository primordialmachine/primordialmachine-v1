/// @file Mkx/Scribe/Cas/Nodes/BinaryPlusNode.h
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/BinaryPlusNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_BinaryPlusNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_BinaryPlusNode* self
  );

static void
Mkx_Scribe_Cas_BinaryPlusNode_constructClass
  (
    Mkx_Scribe_Cas_BinaryPlusNode_Class *self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_BinaryPlusNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_BinaryPlusNode_visit,
                         &Mkx_Scribe_Cas_BinaryPlusNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_BinaryPlusNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_BinaryPlusNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_BinaryPlusNode *self
  )
{
  if (self->leftOperand)
  {
    Ring2_Gc_visit(gc, self->leftOperand);
  }
  if (self->rightOperand)
  {
    Ring2_Gc_visit(gc, self->rightOperand);
  }
}

static void
check
  (
    Mkx_Scribe_Cas_Node *node
  )
{
  if (!node)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_BinaryPlus != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_BinaryPlusNode* binaryPlusNode = Ring1_cast(Mkx_Scribe_Cas_BinaryPlusNode*, node);
  if (!binaryPlusNode->leftOperand || !binaryPlusNode->rightOperand)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_BinaryPlusNode *
clone
  (
    Mkx_Scribe_Cas_BinaryPlusNode *self
  )
{
  return Mkx_Scribe_Cas_BinaryPlusNode_create(self->leftOperand ? Mkx_Scribe_Cas_Node_clone(self->leftOperand) : NULL,
                                              self->rightOperand ? Mkx_Scribe_Cas_Node_clone(self->rightOperand) : NULL);
}

static void
emit
  (
    Mkx_Scribe_Cas_BinaryPlusNode *self,
    Mkx_Scribe_Cas_EmissionContext *emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->leftOperand);
  Ring2_String* plusString = Ring2_String_fromC(false, " + ");
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_OutputNode_create(plusString)));
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->rightOperand);
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_BinaryPlusNode* self
  )
{ return 2; }

static Mkx_Scribe_Cas_Node*
evaluateVectorVector
  (
    Mkx_Scribe_Cas_VectorNode* leftOperand,
    Mkx_Scribe_Cas_VectorNode* rightOperand,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  if (Mkx_Scribe_Cas_VectorNode_getNumberOfElements(leftOperand) != 
      Mkx_Scribe_Cas_VectorNode_getNumberOfElements(rightOperand))
  {
    Ring1_Log_error("%s:%d: operand vectors must be of the same dimensionality\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  int64_t n = Mkx_Scribe_Cas_VectorNode_getNumberOfElements(leftOperand);
  Mkx_Scribe_Cas_VectorNode* result = Mkx_Scribe_Cas_VectorNode_create(n);
  for (int64_t i = 0; i < n; ++i)
  {
    Mkx_Scribe_Cas_Node* x = Mkx_Scribe_Cas_VectorNode_getElement(leftOperand, i),
                        * y = Mkx_Scribe_Cas_VectorNode_getElement(rightOperand, i);
    Mkx_Scribe_Cas_Node* z = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryPlusNode_create(x, y));
    Mkx_Scribe_Cas_VectorNode_setElement(result, i, z);
  }
  return Ring1_cast(Mkx_Scribe_Cas_Node*, result);
}

static Mkx_Scribe_Cas_Node *
evaluateMatrixMatrix
  (
    Mkx_Scribe_Cas_MatrixNode *leftOperand,
    Mkx_Scribe_Cas_MatrixNode *rightOperand,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  if (Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(leftOperand) != Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(rightOperand) ||
      Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(leftOperand) != Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(rightOperand))
  {
    Ring1_Log_error("%s:%d: operand matrix must be of the same dimensionality\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  int64_t n = Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(leftOperand),
          m = Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(leftOperand);
  Mkx_Scribe_Cas_MatrixNode* result = Mkx_Scribe_Cas_MatrixNode_create(n, m);
  for (int64_t i = 0; i < n; ++i)
  {
    for (int64_t j = 0; j < m; ++j)
    {
      Mkx_Scribe_Cas_Node* x = Mkx_Scribe_Cas_MatrixNode_getElement(leftOperand, i, j),
                         * y = Mkx_Scribe_Cas_MatrixNode_getElement(rightOperand, i, j);
      Mkx_Scribe_Cas_Node *z = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_BinaryPlusNode_create(x, y));
      Mkx_Scribe_Cas_MatrixNode_setElement(result, i, j, z);
    }
  }
  return Ring1_cast(Mkx_Scribe_Cas_Node *, result);
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_BinaryPlusNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  static const bool OPTIMIZE = true;
  
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  if (Mkx_Scribe_Cas_NodeKind_Matrix == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
      Mkx_Scribe_Cas_NodeKind_Matrix == Mkx_Scribe_Cas_Node_getKind(self->rightOperand))
  {
    return evaluateMatrixMatrix(Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, self->leftOperand),
                                Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, self->rightOperand),
                                evaluationContext);
  }
  else if (Mkx_Scribe_Cas_NodeKind_Vector == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
           Mkx_Scribe_Cas_NodeKind_Vector == Mkx_Scribe_Cas_Node_getKind(self->rightOperand))
  {
    return evaluateVectorVector(Ring1_cast(Mkx_Scribe_Cas_VectorNode*, self->leftOperand),
                                Ring1_cast(Mkx_Scribe_Cas_VectorNode*, self->rightOperand),
                                evaluationContext);
  }

  if (OPTIMIZE)
  {
    // 1 + 0, 0 + 1 -> 1
    bool returnOne = false;
    returnOne |= Mkx_Scribe_Cas_NodeKind_One == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
                 Mkx_Scribe_Cas_NodeKind_Zero == Mkx_Scribe_Cas_Node_getKind(self->rightOperand);
    returnOne |= Mkx_Scribe_Cas_NodeKind_Zero == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
                 Mkx_Scribe_Cas_NodeKind_One == Mkx_Scribe_Cas_Node_getKind(self->rightOperand);
    // 0 + 0 -> 0
    bool returnZero = false;
    returnZero |= Mkx_Scribe_Cas_NodeKind_Zero == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
                  Mkx_Scribe_Cas_NodeKind_Zero == Mkx_Scribe_Cas_Node_getKind(self->rightOperand);
    if (returnOne)
    {
      return Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
    }
    else if (returnZero)
    {
      return Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
    }

    // e + 0 -> e, kind(e) != matrix
    bool returnRightOperand = false;
    returnRightOperand |= Mkx_Scribe_Cas_NodeKind_Zero == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
                          Mkx_Scribe_Cas_NodeKind_Matrix != Mkx_Scribe_Cas_Node_getKind(self->rightOperand);
    if (returnRightOperand)
    {
      return self->rightOperand;
    }

    // e + 0 -> e, kind(e) != matrix
    bool returnLeftOperand = false;
    returnLeftOperand |= Mkx_Scribe_Cas_NodeKind_Matrix != Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
                         Mkx_Scribe_Cas_NodeKind_Zero == Mkx_Scribe_Cas_Node_getKind(self->rightOperand);
    if (returnLeftOperand)
    {
      return self->leftOperand;
    }

    return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
  }
  else
  {
    return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
  }
}

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_BinaryPlusNode* self,
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
    Mkx_Scribe_Cas_BinaryPlusNode* self,
    int64_t index,
    Mkx_Scribe_Cas_Node *node
  )
{
  switch (index)
  {
  case 0:
  { self->leftOperand = node; } break;
  case 1:
  { self->rightOperand = node; } break;
  default:
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  };
}

void
Mkx_Scribe_Cas_BinaryPlusNode_construct
  (
    Mkx_Scribe_Cas_BinaryPlusNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_BinaryPlus;
  self->leftOperand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[0]));
  self->rightOperand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[1]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_BinaryPlusNode_getType());
}

Mkx_Scribe_Cas_BinaryPlusNode*
Mkx_Scribe_Cas_BinaryPlusNode_create
  (
    Mkx_Scribe_Cas_Node *leftOperand,
    Mkx_Scribe_Cas_Node *rightOperand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_BinaryPlusNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,leftOperand));
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,rightOperand));
  Mkx_Scribe_Cas_BinaryPlusNode* self = Ring1_cast(Mkx_Scribe_Cas_BinaryPlusNode*,
                                                   Machine_allocateClassObject(ty,
                                                                               NUMBER_OF_ARGUMENTS,
                                                                               arguments));
  return self;
}

static void
Mkx_Scribe_Cas_BinaryPlusNode_constructClass
  (
    Mkx_Scribe_Cas_BinaryPlusNode_Class *self
  )
{ 
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext *)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
