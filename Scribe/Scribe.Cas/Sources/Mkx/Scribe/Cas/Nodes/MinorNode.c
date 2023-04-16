/// @file Mkx/Scribe/Cas/Nodes/MinorNode.h
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/MinorNode.h"

#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_MinorNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_MinorNode* self
  );

static void
Mkx_Scribe_Cas_MinorNode_constructClass
  (
    Mkx_Scribe_Cas_MinorNode_Class *self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_MinorNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_MinorNode_visit,
                         &Mkx_Scribe_Cas_MinorNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_MinorNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_MinorNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_MinorNode *self
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
  if (Mkx_Scribe_Cas_NodeKind_Minor != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_MinorNode *minorNode = Ring1_cast(Mkx_Scribe_Cas_MinorNode *, node);
  if (!minorNode->operand)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }

  if (Mkx_Scribe_Cas_NodeKind_Matrix != Mkx_Scribe_Cas_Node_getKind(minorNode->operand))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_MatrixNode* matrixNode = Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, minorNode->operand);
  if (Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(matrixNode) != Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(matrixNode))
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_MinorNode*
clone
  (
    Mkx_Scribe_Cas_MinorNode* self
  )
{
  return Mkx_Scribe_Cas_MinorNode_create(self->rowIndex, self->columnIndex, self->operand ? Mkx_Scribe_Cas_Node_clone(self->operand) : NULL);
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_MinorNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_MatrixNode* subMatrixNode = Ring1_cast(Mkx_Scribe_Cas_MatrixNode *, Mkx_Scribe_Cas_Node_clone(self->operand));

  Mkx_Scribe_Cas_MatrixNode_deleteRow(subMatrixNode, self->rowIndex);
  Mkx_Scribe_Cas_MatrixNode_deleteColumn(subMatrixNode, self->columnIndex);
  
  return Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_DeterminantNode_create(Ring1_cast(Mkx_Scribe_Cas_Node *, subMatrixNode)));
}

static void
emit
  (
    Mkx_Scribe_Cas_MinorNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  /// @todo Emit the row and the column index.
  Mkx_Scribe_Cas_Node* minor = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "minor"))),
                     * leftParenthesis = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "("))),
                     * rightParenthesis = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ")")));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, minor);
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, leftParenthesis);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->operand);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rightParenthesis);
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_MinorNode* self
  )
{ return 1; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_MinorNode* self,
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
    Mkx_Scribe_Cas_MinorNode* self,
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
Mkx_Scribe_Cas_MinorNode_construct
  (
    Mkx_Scribe_Cas_MinorNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_Minor;
  self->rowIndex = Ring2_Value_getInteger(&arguments[0]);
  self->columnIndex = Ring2_Value_getInteger(&arguments[1]);
  self->operand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[2]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_MinorNode_getType());
}

Mkx_Scribe_Cas_MinorNode*
Mkx_Scribe_Cas_MinorNode_create
  (
    int64_t rowIndex,
    int64_t columnIndex,
    Mkx_Scribe_Cas_Node* operand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_MinorNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&arguments[0], rowIndex);
  Ring2_Value_setInteger(&arguments[1], columnIndex);
  Ring2_Value_setObject(&arguments[2], Ring1_cast(Machine_Object*,operand));
  Mkx_Scribe_Cas_MinorNode* self = Ring1_cast(Mkx_Scribe_Cas_MinorNode*,
                                              Machine_allocateClassObject(ty,
                                                                          NUMBER_OF_ARGUMENTS,
                                                                          arguments));
  return self;
}

static void
Mkx_Scribe_Cas_MinorNode_constructClass
  (
    Mkx_Scribe_Cas_MinorNode_Class *self
  )
{ 
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*,Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
