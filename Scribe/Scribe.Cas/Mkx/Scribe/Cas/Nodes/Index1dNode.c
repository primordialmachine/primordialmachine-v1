/// @file Mkx/Scribe/Cas/Nodes/Index1dNode.c
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/Index1dNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_Index1dNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_Index1dNode* self
  );

static void
Mkx_Scribe_Cas_Index1dNode_constructClass
  (
    Mkx_Scribe_Cas_Index1dNode_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_Index1dNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_Index1dNode_visit,
                         &Mkx_Scribe_Cas_Index1dNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_Index1dNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_Index1dNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_Index1dNode *self
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
  if (Mkx_Scribe_Cas_NodeKind_Index1d != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_Index1dNode* index1dNode = Ring1_cast(Mkx_Scribe_Cas_Index1dNode*, node);
  if (!index1dNode->operand)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_Index1dNode*
clone
  (
    Mkx_Scribe_Cas_Index1dNode* self
  )
{
  return Mkx_Scribe_Cas_Index1dNode_create(self->index, self->operand);
}

static Mkx_Scribe_Cas_Node *
evaluate
  (
    Mkx_Scribe_Cas_Index1dNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));
  return Ring1_cast(Mkx_Scribe_Cas_Node *, self);
}

static void
emit
  (
    Mkx_Scribe_Cas_Index1dNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->operand);

  Ring2_String* indexString = NULL;
  switch (emissionContext->indexEmissionOption)
  {
  case Mkx_Scribe_Cas_IndexEmissionOption_Cxx:
  { indexString = Ring2_String_printf(Ring2_Context_get(), Ring2_String_fromC(false, "[%i]"), self->index); } break;
  case Mkx_Scribe_Cas_IndexEmissionOption_Hll:
  { indexString = Ring2_String_printf(Ring2_Context_get(), Ring2_String_fromC(false, "[%i]"), self->index); } break;
  default:
  {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump(); 
  }
  };
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_OutputNode_create(indexString)));
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_Index1dNode* self
  )
{ return 1; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_Index1dNode* self,
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
    Mkx_Scribe_Cas_Index1dNode* self,
    int64_t index,
    Mkx_Scribe_Cas_Node *node
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
Mkx_Scribe_Cas_Index1dNode_construct
  (
    Mkx_Scribe_Cas_Index1dNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_Index1d;
  self->index = Ring2_Value_getInteger(&arguments[0]);
  self->operand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[1]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_Index1dNode_getType());
}

Mkx_Scribe_Cas_Index1dNode*
Mkx_Scribe_Cas_Index1dNode_create
  (
    int64_t index,
    Mkx_Scribe_Cas_Node* operand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_Index1dNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&arguments[0], index);
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,operand));
  Mkx_Scribe_Cas_Index1dNode* self = Ring1_cast(Mkx_Scribe_Cas_Index1dNode*,
                                                Machine_allocateClassObject(ty,
                                                                            NUMBER_OF_ARGUMENTS,
                                                                            arguments));
  return self;
}

static void
Mkx_Scribe_Cas_Index1dNode_constructClass
  (
    Mkx_Scribe_Cas_Index1dNode_Class* self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node *(*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
