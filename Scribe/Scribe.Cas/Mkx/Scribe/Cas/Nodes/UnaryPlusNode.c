/// @file Mkx/Scribe/Cas/Nodes/UnaryPlusNode.c
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/UnaryPlusNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_UnaryPlusNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_UnaryPlusNode* self
  );

static void
Mkx_Scribe_Cas_UnaryPlusNode_constructClass
  (
    Mkx_Scribe_Cas_UnaryPlusNode_Class *self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_UnaryPlusNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_UnaryPlusNode_visit,
                         &Mkx_Scribe_Cas_UnaryPlusNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_UnaryPlusNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_UnaryPlusNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_UnaryPlusNode *self
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
  if (Mkx_Scribe_Cas_NodeKind_UnaryPlus != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_UnaryPlusNode *unaryPlusNode = Ring1_cast(Mkx_Scribe_Cas_UnaryPlusNode *, node);
  if (!unaryPlusNode->operand)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_UnaryPlusNode*
clone
  (
    Mkx_Scribe_Cas_UnaryPlusNode* self
  )
{
  return Mkx_Scribe_Cas_UnaryPlusNode_create(self->operand ? Mkx_Scribe_Cas_Node_clone(self->operand) : NULL);
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_UnaryPlusNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  static const bool OPTIMIZE = true;

  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  if (OPTIMIZE)
  {
    bool returnOperand = false;
    returnOperand |= Mkx_Scribe_Cas_NodeKind_Matrix == Mkx_Scribe_Cas_Node_getKind(self->operand);
    returnOperand |= Mkx_Scribe_Cas_NodeKind_Zero == Mkx_Scribe_Cas_Node_getKind(self->operand);
    returnOperand |= Mkx_Scribe_Cas_NodeKind_One == Mkx_Scribe_Cas_Node_getKind(self->operand);
    returnOperand |= Mkx_Scribe_Cas_NodeKind_Variable == Mkx_Scribe_Cas_Node_getKind(self->operand);
    returnOperand |= Mkx_Scribe_Cas_NodeKind_Group == Mkx_Scribe_Cas_Node_getKind(self->operand);
    if (returnOperand)
    {
      return self->operand;
    }
  }

  return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
}

static void
emit
  (
    Mkx_Scribe_Cas_UnaryPlusNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Ring2_String* plusString = Ring2_String_fromC(false, "+");
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_OutputNode_create(plusString)));
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->operand);
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_UnaryPlusNode* self
  )
{ return 1; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_UnaryPlusNode* self,
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
    Mkx_Scribe_Cas_UnaryPlusNode* self,
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
    Ring1_Log_error("%s:%d: index out of range\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  };
}

void
Mkx_Scribe_Cas_UnaryPlusNode_construct
  (
    Mkx_Scribe_Cas_UnaryPlusNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_UnaryPlus;
  self->operand = (Mkx_Scribe_Cas_Node *)Ring2_Value_getObject(&arguments[0]);
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_UnaryPlusNode_getType());
}

Mkx_Scribe_Cas_UnaryPlusNode*
Mkx_Scribe_Cas_UnaryPlusNode_create
  (
    Mkx_Scribe_Cas_Node* operand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_UnaryPlusNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,operand));
  Mkx_Scribe_Cas_UnaryPlusNode* self = Ring1_cast(Mkx_Scribe_Cas_UnaryPlusNode*,
                                                  Machine_allocateClassObject(ty,
                                                                              NUMBER_OF_ARGUMENTS,
                                                                              arguments));
  return self;
}

static void
Mkx_Scribe_Cas_UnaryPlusNode_constructClass
  (
    Mkx_Scribe_Cas_UnaryPlusNode_Class *self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
