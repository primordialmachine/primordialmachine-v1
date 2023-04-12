/// @file Mkx/Scribe/Cas/Nodes/OneNode.c
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/OneNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_OneNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_OneNode* self
  );

static void
Mkx_Scribe_Cas_OneNode_constructClass
  (
    Mkx_Scribe_Cas_OneNode_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_OneNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_OneNode_visit,
                         &Mkx_Scribe_Cas_OneNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_OneNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_OneNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_OneNode *self
  )
{ }

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
  if (Mkx_Scribe_Cas_NodeKind_One != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_OneNode*
clone
  (
    Mkx_Scribe_Cas_OneNode* self
  )
{
  return Mkx_Scribe_Cas_OneNode_create();
}

static Mkx_Scribe_Cas_Node *
evaluate
  (
    Mkx_Scribe_Cas_OneNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));
  return Ring1_cast(Mkx_Scribe_Cas_Node *, self);
}

static void
emit
  (
    Mkx_Scribe_Cas_OneNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Ring2_String* oneString = Ring2_String_fromC(false, "1");
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_OutputNode_create(oneString)));
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_OneNode* self
  )
{ return 0; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_OneNode* self,
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
    Mkx_Scribe_Cas_OneNode* self,
    int64_t index,
    Mkx_Scribe_Cas_Node *node
  )
{
  Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
  Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
  Ring2_jump();
}

void
Mkx_Scribe_Cas_OneNode_construct
  (
    Mkx_Scribe_Cas_OneNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_One;
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_OneNode_getType());
}

Mkx_Scribe_Cas_OneNode*
Mkx_Scribe_Cas_OneNode_create
  (
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_OneNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Mkx_Scribe_Cas_OneNode* self = Ring1_cast(Mkx_Scribe_Cas_OneNode*,
                                            Machine_allocateClassObject(ty,
                                                                        NUMBER_OF_ARGUMENTS,
                                                                        ARGUMENTS));
  return self;
}

static void
Mkx_Scribe_Cas_OneNode_constructClass
  (
    Mkx_Scribe_Cas_OneNode_Class* self
  )
{ 
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node *(*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
