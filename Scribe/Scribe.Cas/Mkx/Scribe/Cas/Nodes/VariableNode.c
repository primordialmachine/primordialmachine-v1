/// @file Mkx/Scribe/Cas/Nodes/VariableNode.c
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/VariableNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_VariableNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_VariableNode* self
  );

static void
Mkx_Scribe_Cas_VariableNode_constructClass
  (
    Mkx_Scribe_Cas_VariableNode_Class *self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_VariableNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_VariableNode_visit,
                         &Mkx_Scribe_Cas_VariableNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_VariableNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_VariableNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_VariableNode *self
  )
{
  if (self->displayName) {
    Ring2_Gc_visit(gc, self->displayName);
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
  if (Mkx_Scribe_Cas_NodeKind_Variable != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_VariableNode*
clone
  (
    Mkx_Scribe_Cas_VariableNode* self
  )
{ return Mkx_Scribe_Cas_VariableNode_create(self->displayName); }

static Mkx_Scribe_Cas_Node *
evaluate
  (
    Mkx_Scribe_Cas_VariableNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));
  return Ring1_cast(Mkx_Scribe_Cas_Node *, self);
}

static void
emit
  (
    Mkx_Scribe_Cas_VariableNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_OutputNode_create(self->displayName)));
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_VariableNode* self
  )
{ return 0; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_VariableNode* self,
    int64_t index
  )
{
  Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
  Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
  Ring2_jump();
}

static void
setChildAt
  (
    Mkx_Scribe_Cas_VariableNode* self,
    int64_t index,
    Mkx_Scribe_Cas_Node *node
  )
{
  Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
  Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
  Ring2_jump();
}

void
Mkx_Scribe_Cas_VariableNode_construct
  (
    Mkx_Scribe_Cas_VariableNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_Variable;
  self->displayName = Ring2_Value_getString(&arguments[0]);
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_VariableNode_getType());
}

Mkx_Scribe_Cas_VariableNode*
Mkx_Scribe_Cas_VariableNode_create
  (
    Ring2_String* displayName
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_VariableNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setString(&arguments[0], displayName);
  Mkx_Scribe_Cas_VariableNode* self = Ring1_cast(Mkx_Scribe_Cas_VariableNode*,
                                                 Machine_allocateClassObject(ty,
                                                                             NUMBER_OF_ARGUMENTS,
                                                                             arguments));
  return self;
}

static void
Mkx_Scribe_Cas_VariableNode_constructClass
  (
    Mkx_Scribe_Cas_VariableNode_Class *self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node *(*)(Mkx_Scribe_Cas_Node*,Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
