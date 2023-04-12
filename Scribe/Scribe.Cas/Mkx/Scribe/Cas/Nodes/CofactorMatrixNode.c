/// @file Mkx/Scribe/Cas/Nodes/CofactorMatrixNode.h
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/CofactorMatrixNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_CofactorMatrixNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_CofactorMatrixNode *self
  );

static void
Mkx_Scribe_Cas_CofactorMatrixNode_constructClass
  (
    Mkx_Scribe_Cas_CofactorMatrixNode_Class *self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_CofactorMatrixNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_CofactorMatrixNode_visit,
                         &Mkx_Scribe_Cas_CofactorMatrixNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_CofactorMatrixNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_CofactorMatrixNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_CofactorMatrixNode *self
  )
{
  if (self->operand) {
    Ring2_Gc_visit(gc, self->operand);
  }
}

static void
check
  (
    Mkx_Scribe_Cas_Node *node
  )
{
  if (!node) {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_CofactorMatrix != Mkx_Scribe_Cas_Node_getKind(node)) {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_CofactorMatrixNode *cofactorMatrixNode = Ring1_cast(Mkx_Scribe_Cas_CofactorMatrixNode *, node);
  if (!cofactorMatrixNode->operand) {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_Matrix != Mkx_Scribe_Cas_Node_getKind(cofactorMatrixNode->operand)) {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_MatrixNode* matrixNode = Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, cofactorMatrixNode->operand);
  // Must be a square matrix of a size greater than 0.
  if (!(Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(matrixNode) == Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(matrixNode)) ||
      !(Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(matrixNode) > 0)) {
    Ring1_Log_error("%s:%d: operand must be a non-empty square matrix\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_CofactorMatrixNode*
clone
  (
    Mkx_Scribe_Cas_CofactorMatrixNode* self
  )
{
  return Mkx_Scribe_Cas_CofactorMatrixNode_create(self->operand ? Mkx_Scribe_Cas_Node_clone(self->operand) : NULL);
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_CofactorMatrixNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_MatrixNode* matrixNode = Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, self->operand);

  int64_t numberOfRows = Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(matrixNode),
          numberOfColumns = Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(matrixNode);
          
  Mkx_Scribe_Cas_MatrixNode *cofactorMatrixNode = Mkx_Scribe_Cas_MatrixNode_create(numberOfRows, numberOfColumns);
  
  for (int64_t i = 0, n = numberOfRows; i < n; ++i) {
    for (int64_t j = 0, m = numberOfColumns; j < m; ++j) {
      Mkx_Scribe_Cas_Node *cofactorNode = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_CofactorNode_create(i, j, Ring1_cast(Mkx_Scribe_Cas_Node *, matrixNode)));
      Mkx_Scribe_Cas_MatrixNode_setElement(cofactorMatrixNode, i, j, cofactorNode);
    }
  }
  return Ring1_cast(Mkx_Scribe_Cas_Node *, cofactorMatrixNode);
}

static void
emit
  (
    Mkx_Scribe_Cas_CofactorMatrixNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_Node
    * cofactorMatrix = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "cofactorMatrix"))),
    * leftParenthesis = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "("))),
    * rightParenthesis = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ")")));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, cofactorMatrix);
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, leftParenthesis);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->operand);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rightParenthesis);
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_CofactorMatrixNode* self
  )
{ return 1; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_CofactorMatrixNode* self,
    int64_t index
  )
{
  switch (index)
  {
  case 0:
    return self->operand;
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
    Mkx_Scribe_Cas_CofactorMatrixNode* self,
    int64_t index,
    Mkx_Scribe_Cas_Node* node
  )
{
  switch (index)
  {
  case 0:
  { self->operand = node; } break;
  default:
  {
    Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  };
}

void
Mkx_Scribe_Cas_CofactorMatrixNode_construct
  (
    Mkx_Scribe_Cas_CofactorMatrixNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_CofactorMatrix;
  self->operand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[0]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_CofactorMatrixNode_getType());
}

Mkx_Scribe_Cas_CofactorMatrixNode*
Mkx_Scribe_Cas_CofactorMatrixNode_create
  (
    Mkx_Scribe_Cas_Node* operand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_CofactorMatrixNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,operand));
  Mkx_Scribe_Cas_CofactorMatrixNode* self = Ring1_cast(Mkx_Scribe_Cas_CofactorMatrixNode*,
                                                       Machine_allocateClassObject(ty,
                                                                                   NUMBER_OF_ARGUMENTS,
                                                                                   arguments));
  return self;
}

static void
Mkx_Scribe_Cas_CofactorMatrixNode_constructClass
  (
    Mkx_Scribe_Cas_CofactorMatrixNode_Class *self
  )
{ 
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
