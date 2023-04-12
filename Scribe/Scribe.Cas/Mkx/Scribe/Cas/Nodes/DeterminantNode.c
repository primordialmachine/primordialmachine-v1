/// @file Mkx/Scribe/Cas/Nodes/DeterminantNode.h
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/DeterminantNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_DeterminantNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_DeterminantNode* self
  );

static void
Mkx_Scribe_Cas_DeterminantNode_constructClass
  (
    Mkx_Scribe_Cas_DeterminantNode_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_DeterminantNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_DeterminantNode_visit,
                         &Mkx_Scribe_Cas_DeterminantNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_DeterminantNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_DeterminantNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_DeterminantNode* self
  )
{
  if (self->operand) {
    Ring2_Gc_visit(gc, self->operand);
  }
}

static void
check
  (
    Mkx_Scribe_Cas_Node* node
  )
{
  if (!node) {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_Determinant != Mkx_Scribe_Cas_Node_getKind(node)) {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_DeterminantNode* determinant = Ring1_cast(Mkx_Scribe_Cas_DeterminantNode*, node);
  if (!determinant->operand) {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_Matrix != Mkx_Scribe_Cas_Node_getKind(determinant->operand)) {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_MatrixNode* matrix = Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, determinant->operand);
  if (Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(matrix) !=
      Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(matrix)) {
    Ring1_Log_error("%s:%d: operand must be a non-empty square matrix\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_DeterminantNode*
clone
  (
    Mkx_Scribe_Cas_DeterminantNode* self
  )
{ return Mkx_Scribe_Cas_DeterminantNode_create(self->operand ? Mkx_Scribe_Cas_Node_clone(self->operand) : NULL); }

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_DeterminantNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_MatrixNode* operand = Ring1_cast(Mkx_Scribe_Cas_MatrixNode*, self->operand);

  int64_t numberOfRows = Mkx_Scribe_Cas_MatrixNode_getNumberOfRows(operand),
          numberOfColumns = Mkx_Scribe_Cas_MatrixNode_getNumberOfColumns(operand);

  if (numberOfRows == 0 && numberOfColumns == 0)
  {
    return Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OneNode_create());
  }
  else if (numberOfRows == 1 && numberOfColumns == 1)
  {
    // See Mkx_Scribe_Cas_NodeKind_Determinant for more information.
    // Terminates recursion.
    return Mkx_Scribe_Cas_MatrixNode_getElement(operand, 0, 0);
  }
  else if (numberOfRows == 2 && numberOfColumns == 2)
  {
    // See Mkx_Scribe_Cas_NodeKind_Determinant for more information.
    // Terminates recursion.
    Mkx_Scribe_Cas_Node* a = Mkx_Scribe_Cas_MatrixNode_getElement(operand, 0, 0),
                       * b = Mkx_Scribe_Cas_MatrixNode_getElement(operand, 0, 1),
                       * c = Mkx_Scribe_Cas_MatrixNode_getElement(operand, 1, 0),
                       * d = Mkx_Scribe_Cas_MatrixNode_getElement(operand, 1, 1);
    Mkx_Scribe_Cas_Node *ad = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_BinaryStarNode_create(a, d));
    Mkx_Scribe_Cas_Node *bc = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_BinaryStarNode_create(b, c));
    return Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryMinusNode_create(ad, bc));
  }
  else
  {
    Mkx_Scribe_Cas_Node* node = NULL;
    // See Mkx_Scribe_Cas_NodeKind_Determinant for more information.
    for (int64_t j = 0, m = numberOfColumns; j < m; ++j)
    {
      Mkx_Scribe_Cas_Node* a = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_GroupNode_create(Mkx_Scribe_Cas_MatrixNode_getElement(operand, 0, j)));
      Mkx_Scribe_Cas_Node* b = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_GroupNode_create(Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_CofactorNode_create(0, j, Ring1_cast(Mkx_Scribe_Cas_Node *, operand)))));
      Mkx_Scribe_Cas_Node* c = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_BinaryStarNode_create(a, b));
      if (node)
      { node = Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_BinaryPlusNode_create(node, c)); }
      else
      { node = c; }
    }
    return node;
  }
}

static void
emit
  (
    Mkx_Scribe_Cas_DeterminantNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_Node
    * determinant = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "determinant"))),
    * leftParenthesis = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, "("))),
    * rightParenthesis = Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(Ring2_String_fromC(false, ")")));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, determinant);
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, leftParenthesis);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->operand);

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, rightParenthesis);
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_DeterminantNode* self
  )
{ return 1; }

static Mkx_Scribe_Cas_Node*
getChildAt
(
  Mkx_Scribe_Cas_DeterminantNode* self,
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
  Mkx_Scribe_Cas_DeterminantNode* self,
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
Mkx_Scribe_Cas_DeterminantNode_construct
  (
    Mkx_Scribe_Cas_DeterminantNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_Determinant;
  self->operand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[0]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_DeterminantNode_getType());
}

Mkx_Scribe_Cas_DeterminantNode*
Mkx_Scribe_Cas_DeterminantNode_create
  (
    Mkx_Scribe_Cas_Node* operand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_DeterminantNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,operand));
  Mkx_Scribe_Cas_DeterminantNode* self = Ring1_cast(Mkx_Scribe_Cas_DeterminantNode*,
                                                    Machine_allocateClassObject(ty,
                                                                                NUMBER_OF_ARGUMENTS,
                                                                                arguments));
  return self;
}

static void
Mkx_Scribe_Cas_DeterminantNode_constructClass
  (
    Mkx_Scribe_Cas_DeterminantNode_Class* self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t(*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
