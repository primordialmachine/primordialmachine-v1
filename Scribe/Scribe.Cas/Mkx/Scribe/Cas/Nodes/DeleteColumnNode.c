/// @file Mkx/Scribe/Cas/Nodes/DeleteColumnNode.h
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/DeleteColumnNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_DeleteColumnNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_DeleteColumnNode* self
  );

static void
Mkx_Scribe_Cas_DeleteColumnNode_constructClass
  (
    Mkx_Scribe_Cas_DeleteColumnNode_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_DeleteColumnNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_DeleteColumnNode_visit,
                         &Mkx_Scribe_Cas_DeleteColumnNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_DeleteColumnNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_DeleteColumnNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_DeleteColumnNode *self
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
  if (Mkx_Scribe_Cas_NodeKind_DeleteColumn != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_DeleteColumnNode * deleteColumnNode = Ring1_cast(Mkx_Scribe_Cas_DeleteColumnNode *, node);
  if (!deleteColumnNode->operand)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }

  if (Mkx_Scribe_Cas_NodeKind_Matrix != Mkx_Scribe_Cas_Node_getKind(deleteColumnNode->operand))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_MatrixNode* matrixNode = Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, deleteColumnNode->operand);
  // Must be within bounds.
  if (deleteColumnNode->columnIndex < 0 || deleteColumnNode->columnIndex >= matrixNode->numberOfColumns)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_DeleteColumnNode*
clone
  (
    Mkx_Scribe_Cas_DeleteColumnNode* self
  )
{
  return Mkx_Scribe_Cas_DeleteColumnNode_create(self->columnIndex, self->operand ? Mkx_Scribe_Cas_Node_clone(self->operand) : NULL);
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_DeleteColumnNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  /// @todo Add and use function to create a matrix with a deleted row.
  Mkx_Scribe_Cas_MatrixNode *matrixNode = Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, Mkx_Scribe_Cas_Node_clone(self->operand));
  Mkx_Scribe_Cas_MatrixNode_deleteColumn(matrixNode, self->columnIndex);

  return Ring1_cast(Mkx_Scribe_Cas_Node*, matrixNode);
}

static void
emit
  (
    Mkx_Scribe_Cas_DeleteColumnNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  // Emit the column index.
  Mkx_Scribe_Cas_Node* index =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_printf(Ring2_Context_get(), Ring2_String_fromC(false, "%i"), self->columnIndex)));
  Mkx_Scribe_Cas_Node* separator =
    Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ", ")));
 Mkx_Scribe_Cas_Node* operatorNameString = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "deleteColumn"))),
                    * leftParenthesisString = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "("))),
                    * rightParenthesisString = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ")")));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, operatorNameString);
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, leftParenthesisString);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, index);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, separator);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->operand);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rightParenthesisString);
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_DeleteColumnNode* self
  )
{ return 1; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_DeleteColumnNode* self,
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
    Mkx_Scribe_Cas_DeleteColumnNode* self,
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
Mkx_Scribe_Cas_DeleteColumnNode_construct
  (
    Mkx_Scribe_Cas_DeleteColumnNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_DeleteColumn;
  self->columnIndex = Ring2_Value_getInteger(&arguments[0]);
  self->operand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[1]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_DeleteColumnNode_getType());
}

Mkx_Scribe_Cas_DeleteColumnNode*
Mkx_Scribe_Cas_DeleteColumnNode_create
  (
    int64_t columnIndex,
    Mkx_Scribe_Cas_Node* operand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_DeleteColumnNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&arguments[0], columnIndex);
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,operand));
  Mkx_Scribe_Cas_DeleteColumnNode* self = Ring1_cast(Mkx_Scribe_Cas_DeleteColumnNode*,
                                                     Machine_allocateClassObject(ty,
                                                                                 NUMBER_OF_ARGUMENTS,
                                                                                 arguments));
  return self;
}

static void
Mkx_Scribe_Cas_DeleteColumnNode_constructClass
  (
    Mkx_Scribe_Cas_DeleteColumnNode_Class* self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
