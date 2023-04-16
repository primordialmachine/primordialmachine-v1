/// @file Mkx/Scribe/Cas/Nodes/TransposeNode.h
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/TransposeNode.h"

#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_TransposeNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_TransposeNode* self
  );

static void
Mkx_Scribe_Cas_TransposeNode_constructClass
  (
    Mkx_Scribe_Cas_TransposeNode_Class *self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_TransposeNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_TransposeNode_visit,
                         &Mkx_Scribe_Cas_TransposeNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_TransposeNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_TransposeNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_TransposeNode *self
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
  if (!node)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_Transpose != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_TransposeNode *matrixTransposeNode = Ring1_cast(Mkx_Scribe_Cas_TransposeNode *, node);
  if (!matrixTransposeNode->operand)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_Matrix != Mkx_Scribe_Cas_Node_getKind(matrixTransposeNode->operand))
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_TransposeNode*
clone
  (
    Mkx_Scribe_Cas_TransposeNode* self
  )
{
  return Mkx_Scribe_Cas_TransposeNode_create(self->operand ? Mkx_Scribe_Cas_Node_clone(self->operand) : NULL);
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_TransposeNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_MatrixNode* oldMatrixNode = Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, self->operand);

  int64_t n = Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(oldMatrixNode),
          m = Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(oldMatrixNode);
          
  Mkx_Scribe_Cas_MatrixNode *newMatrixNode = Mkx_Scribe_Cas_MatrixNode_create(m, n);
          
  if (n == m)
  {
    // Symmetric case.
    // Same code as non-symmetric case at the moment.
    for (int64_t i = 0; i < n; ++i)
    {
      for (int64_t j = 0; j < m; ++j)
      {
        Mkx_Scribe_Cas_Node *element = Mkx_Scribe_Cas_MatrixNode_getElement(oldMatrixNode, i, j);
        Mkx_Scribe_Cas_MatrixNode_setElement(newMatrixNode, j, i, element);
      }
    }
  }
  else
  {
    // Non-symmetric case.
    // Same code as symmetric case at the moment.
    for (int64_t i = 0; i < n; ++i)
    {
      for (int64_t j = 0; j < m; ++j)
      {
        Mkx_Scribe_Cas_Node *element = Mkx_Scribe_Cas_MatrixNode_getElement(oldMatrixNode, i, j);
        Mkx_Scribe_Cas_MatrixNode_setElement(newMatrixNode, j, i, element);
      }
    }
  }
  
  return Ring1_cast(Mkx_Scribe_Cas_Node *, newMatrixNode);
}

static void
emit
  (
    Mkx_Scribe_Cas_TransposeNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_Node
    * transpose = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "transpose"))),
    * leftParenthesis = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "("))),
    * rightParenthesis = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ")")));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, transpose);
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, leftParenthesis);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->operand);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rightParenthesis);
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_TransposeNode* self
  )
{ return 1; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_TransposeNode* self,
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
    Mkx_Scribe_Cas_TransposeNode* self,
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
Mkx_Scribe_Cas_TransposeNode_construct
  (
    Mkx_Scribe_Cas_TransposeNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_Transpose;
  self->operand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[0]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_TransposeNode_getType());
}

Mkx_Scribe_Cas_TransposeNode*
Mkx_Scribe_Cas_TransposeNode_create
  (
    Mkx_Scribe_Cas_Node* operand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_TransposeNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,operand));
  Mkx_Scribe_Cas_TransposeNode* self = Ring1_cast(Mkx_Scribe_Cas_TransposeNode*,
                                                  Machine_allocateClassObject(ty,
                                                                              NUMBER_OF_ARGUMENTS,
                                                                              arguments));
  return self;
}

static void
Mkx_Scribe_Cas_TransposeNode_constructClass
  (
    Mkx_Scribe_Cas_TransposeNode_Class *self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*,Mkx_Scribe_Cas_EvaluationContext *)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
