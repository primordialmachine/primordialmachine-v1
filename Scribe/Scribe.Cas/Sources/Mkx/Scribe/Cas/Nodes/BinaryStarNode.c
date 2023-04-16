/// @file Mkx/Scribe/Cas/Nodes/BinaryStarNode.h
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/BinaryStarNode.h"

#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_BinaryStarNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_BinaryStarNode *self
  );

static void
Mkx_Scribe_Cas_BinaryStarNode_constructClass
  (
    Mkx_Scribe_Cas_BinaryStarNode_Class *self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_BinaryStarNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_BinaryStarNode_visit,
                         &Mkx_Scribe_Cas_BinaryStarNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_BinaryStarNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_BinaryStarNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_BinaryStarNode* self
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
  if (Mkx_Scribe_Cas_NodeKind_BinaryStar != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_BinaryStarNode* binaryStarNode = Ring1_cast(Mkx_Scribe_Cas_BinaryStarNode*, node);
  if (!binaryStarNode->leftOperand || !binaryStarNode->rightOperand)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_BinaryStarNode*
clone
  (
    Mkx_Scribe_Cas_BinaryStarNode* self
  )
{
  return Mkx_Scribe_Cas_BinaryStarNode_create(self->leftOperand ? Mkx_Scribe_Cas_Node_clone(self->leftOperand) : NULL,
                                              self->rightOperand ? Mkx_Scribe_Cas_Node_clone(self->rightOperand) : NULL);
}

static void
emit
  (
    Mkx_Scribe_Cas_BinaryStarNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->leftOperand);
  Ring2_String* starString = Ring2_String_fromC(false, " * ");
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
  int64_t n = Mkx_Scribe_Cas_VectorNode_getNumberOfElements(leftOperand);

  Mkx_Scribe_Cas_VectorNode* result = Mkx_Scribe_Cas_VectorNode_create(n);

  for (int64_t i = 0; i < n; ++i)
  {
    Mkx_Scribe_Cas_Node* e1 = Mkx_Scribe_Cas_VectorNode_getElement(leftOperand, i);
    Mkx_Scribe_Cas_Node* e2 = Mkx_Scribe_Cas_VectorNode_getElement(rightOperand, i);
    e1 = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_GroupNode_create(e1));
    e2 = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_GroupNode_create(e2));
    Mkx_Scribe_Cas_Node* e = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(e1, e2));
    Mkx_Scribe_Cas_VectorNode_setElement(result, i, e);
  }

  return Ring1_cast(Mkx_Scribe_Cas_Node*, result);
}


static Mkx_Scribe_Cas_Node*
evaluateVariableVector
  (
    Mkx_Scribe_Cas_VariableNode* leftOperand,
    Mkx_Scribe_Cas_VectorNode* rightOperand,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  int64_t n = Mkx_Scribe_Cas_VectorNode_getNumberOfElements(rightOperand);

  Mkx_Scribe_Cas_VectorNode* result = Mkx_Scribe_Cas_VectorNode_create(n);

  for (int64_t i = 0; i < n; ++i)
  {
      Mkx_Scribe_Cas_Node* e1 = Ring1_cast(Mkx_Scribe_Cas_Node*, leftOperand);
      Mkx_Scribe_Cas_Node* e2 = Mkx_Scribe_Cas_VectorNode_getElement(rightOperand, i);
      e2 = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_GroupNode_create(e2));
      Mkx_Scribe_Cas_Node* e = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(e1, e2));
      Mkx_Scribe_Cas_VectorNode_setElement(result, i, e);
  }
  return Ring1_cast(Mkx_Scribe_Cas_Node*, result);
}

static Mkx_Scribe_Cas_Node*
evaluateVariableMatrix
  (
    Mkx_Scribe_Cas_VariableNode* leftOperand,
    Mkx_Scribe_Cas_MatrixNode* rightOperand,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  int64_t n = Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(rightOperand),
          m = Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(rightOperand);

  Mkx_Scribe_Cas_MatrixNode* result = Mkx_Scribe_Cas_MatrixNode_create(n, m);

  for (int64_t i = 0; i < n; ++i)
  {
    for (int64_t j = 0; j < m; ++j)
    {
      Mkx_Scribe_Cas_Node* e1 = Ring1_cast(Mkx_Scribe_Cas_Node*, leftOperand);
      Mkx_Scribe_Cas_Node* e2 = Mkx_Scribe_Cas_MatrixNode_getElement(rightOperand, i, j);
      e2 = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_GroupNode_create(e2));
      Mkx_Scribe_Cas_Node* e = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(e1, e2));
      Mkx_Scribe_Cas_MatrixNode_setElement(result, i, j, e);
    }
  }
  return Ring1_cast(Mkx_Scribe_Cas_Node*, result);
}

static Mkx_Scribe_Cas_Node*
evaluateMatrixMatrix
  (
    Mkx_Scribe_Cas_MatrixNode* leftOperand,
    Mkx_Scribe_Cas_MatrixNode* rightOperand,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  // The number of columns in the first matrix must be equal to the number of rows in the second matrix.
  // The product matrix has the number of rows of the first and the number of columns of the second matrix. 
  // Or in other terms: If A is a l \times m and B is an m \times n matrix, the product matrix is an l \times n.
  if (Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(leftOperand) != Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(rightOperand))
  {
    Ring1_Log_error("%s:%d: number of columns of first operand matrix must be equal to number of rows of second operand matrix\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  int64_t
    l = Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(leftOperand),
    m = Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(rightOperand),
    n = Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(rightOperand);
  Mkx_Scribe_Cas_MatrixNode* result = Mkx_Scribe_Cas_MatrixNode_create(n, m);
  
  // number of rows of the first matrix/number of rows of the result matrix
  for (int64_t i = 0; i < l; ++i)
  {
    // number of columns of the second matrix/number of columns of the result matrix
    for (int64_t j = 0; j < m; ++j)
    {
      Mkx_Scribe_Cas_Node* e = Ring1_cast(Mkx_Scribe_Cas_Node *,Mkx_Scribe_Cas_ZeroNode_create());
      // number of columns of the first matrix/number of rows of the second matrix
      for (int64_t k = 0; k < n; ++k)
      {
        Mkx_Scribe_Cas_Node* e1 = Mkx_Scribe_Cas_MatrixNode_getElement(leftOperand, i, k),
                           * e2 = Mkx_Scribe_Cas_MatrixNode_getElement(rightOperand, k, j);
        e2 = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_GroupNode_create(e2));
        Mkx_Scribe_Cas_Node* e3 = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(e1, e2));
        e = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_BinaryPlusNode_create(e, e3));
      }
      Mkx_Scribe_Cas_MatrixNode_setElement(result, i, j, e);
    }
  }
  return Ring1_cast(Mkx_Scribe_Cas_Node*, result);
}

static Mkx_Scribe_Cas_Node*
evaluateMatrixVector
  (
    Mkx_Scribe_Cas_MatrixNode* leftOperand,
    Mkx_Scribe_Cas_VectorNode* rightOperand,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  // The number of columns of the matrix must be equal to the number of columns of the vector.
  if (Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(leftOperand) != Mkx_Scribe_Cas_VectorNode_getNumberOfElements(rightOperand))
  {
    Ring1_Log_error("%s:%d: number of columns of first operand matrix must be equal to number of elements of second operand vector\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  int64_t n = Mkx_Scribe_Cas_VectorNode_getNumberOfElements(rightOperand);
  int64_t numberOfRows = Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(leftOperand);
  int64_t numberOfElements = Mkx_Scribe_Cas_VectorNode_getNumberOfElements(rightOperand);
  Mkx_Scribe_Cas_VectorNode* result = Mkx_Scribe_Cas_VectorNode_create(numberOfElements);

  // Iterate over the rows.
  for (int64_t i = 0; i < numberOfRows; ++i)
  {
    Mkx_Scribe_Cas_Node* e0 = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
    // Iterate over the elements/columns.
    for (int64_t j = 0; j < numberOfElements; ++j)
    {
        Mkx_Scribe_Cas_Node* e1 = Ring1_cast(Mkx_Scribe_Cas_Node *,Mkx_Scribe_Cas_BinaryStarNode_create(Mkx_Scribe_Cas_MatrixNode_getElement(leftOperand, i, j),
                                                                                                  Mkx_Scribe_Cas_VectorNode_getElement(rightOperand, j)));
        e0  = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_BinaryPlusNode_create(e0, e1));

    }
    Mkx_Scribe_Cas_VectorNode_setElement(result, i, e0);
  }
  return Ring1_cast(Mkx_Scribe_Cas_Node*, result);
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_BinaryStarNode* self,
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
  else if (Mkx_Scribe_Cas_NodeKind_Variable == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
           Mkx_Scribe_Cas_NodeKind_Matrix == Mkx_Scribe_Cas_Node_getKind(self->rightOperand))
  {
    return evaluateVariableMatrix(Ring1_cast(Mkx_Scribe_Cas_VariableNode*, self->leftOperand),
                                  Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, self->rightOperand),
                                  evaluationContext);
  }
  else if (Mkx_Scribe_Cas_NodeKind_Matrix == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
           Mkx_Scribe_Cas_NodeKind_Vector == Mkx_Scribe_Cas_Node_getKind(self->rightOperand))
  {
    return evaluateMatrixVector(Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, self->leftOperand),
                                Ring1_cast(Mkx_Scribe_Cas_VectorNode*, self->rightOperand),
                                evaluationContext);
  }
  else if (Mkx_Scribe_Cas_NodeKind_Variable == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) &&
           Mkx_Scribe_Cas_NodeKind_Vector == Mkx_Scribe_Cas_Node_getKind(self->rightOperand))
  {
    return evaluateVariableVector(Ring1_cast(Mkx_Scribe_Cas_VariableNode*, self->leftOperand),
                                  Ring1_cast(Mkx_Scribe_Cas_VectorNode*, self->rightOperand),
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
    if (Mkx_Scribe_Cas_NodeKind_Zero == Mkx_Scribe_Cas_Node_getKind(self->leftOperand) ||
        Mkx_Scribe_Cas_NodeKind_Zero == Mkx_Scribe_Cas_Node_getKind(self->rightOperand))
    {
      return Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_ZeroNode_create());
    }
    else if (Mkx_Scribe_Cas_NodeKind_One == Mkx_Scribe_Cas_Node_getKind(self->leftOperand))
    {
      return self->rightOperand;
    }
    else if (Mkx_Scribe_Cas_NodeKind_One == Mkx_Scribe_Cas_Node_getKind(self->rightOperand))
    {
      return self->leftOperand;
    }
    else
    {
      return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
    }
  }
  else
  {
    return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
  }
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_BinaryStarNode* self
  )
{ return 2; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_BinaryStarNode* self,
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
    Mkx_Scribe_Cas_BinaryStarNode* self,
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
Mkx_Scribe_Cas_BinaryStarNode_construct
  (
    Mkx_Scribe_Cas_BinaryStarNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_BinaryStar;
  self->leftOperand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[0]));
  self->rightOperand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[1]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_BinaryStarNode_getType());
}

Mkx_Scribe_Cas_BinaryStarNode*
Mkx_Scribe_Cas_BinaryStarNode_create
  (
    Mkx_Scribe_Cas_Node* leftOperand,
    Mkx_Scribe_Cas_Node* rightOperand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_BinaryStarNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,leftOperand));
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,rightOperand));
  Mkx_Scribe_Cas_BinaryStarNode* self = Ring1_cast(Mkx_Scribe_Cas_BinaryStarNode*,
                                                   Machine_allocateClassObject(ty,
                                                                               NUMBER_OF_ARGUMENTS,
                                                                               arguments));
  return self;
}

static void
Mkx_Scribe_Cas_BinaryStarNode_constructClass
  (
    Mkx_Scribe_Cas_BinaryStarNode_Class *self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t(*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
