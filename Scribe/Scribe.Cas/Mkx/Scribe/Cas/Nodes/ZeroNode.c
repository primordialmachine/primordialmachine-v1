/// @file Mkx/Scribe/Cas/Nodes/ZeroNode.c
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/ZeroNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_ZeroNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_ZeroNode* self
  );

static void
Mkx_Scribe_Cas_ZeroNode_constructClass
  (
    Mkx_Scribe_Cas_ZeroNode_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_ZeroNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_ZeroNode_visit,
                         &Mkx_Scribe_Cas_ZeroNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_ZeroNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_ZeroNode_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_ZeroNode *self
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
  if (Mkx_Scribe_Cas_NodeKind_Zero != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_ZeroNode*
clone
  (
    Mkx_Scribe_Cas_ZeroNode* self
  )
{
  return Mkx_Scribe_Cas_ZeroNode_create();
}

static Mkx_Scribe_Cas_Node *
evaluate
  (
    Mkx_Scribe_Cas_ZeroNode* self,
    Mkx_Scribe_Cas_EvaluationContext *evaluationContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));
  return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
}

static void
emit
  (
    Mkx_Scribe_Cas_ZeroNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  Ring2_String* zeroString = Ring2_String_fromC(false, "0");
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, Ring1_cast(Mkx_Scribe_Cas_Node *, Mkx_Scribe_Cas_OutputNode_create(zeroString)));}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_ZeroNode* self
  )
{ return 0; }

static Mkx_Scribe_Cas_Node *
getChildAt
  (
    Mkx_Scribe_Cas_ZeroNode* self,
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
    Mkx_Scribe_Cas_ZeroNode* self,
    int64_t index,
    Mkx_Scribe_Cas_Node *node
  )
{
  Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
  Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
  Ring2_jump();
}

void
Mkx_Scribe_Cas_ZeroNode_construct
  (
    Mkx_Scribe_Cas_ZeroNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_Zero;
  Machine_setClassType(Ring1_cast(Machine_Object*,self), Mkx_Scribe_Cas_ZeroNode_getType());
}

Mkx_Scribe_Cas_ZeroNode*
Mkx_Scribe_Cas_ZeroNode_create
  (
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_ZeroNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[1] = { Ring2_Value_StaticInitializerVoid() };
  Mkx_Scribe_Cas_ZeroNode* self = Ring1_cast(Mkx_Scribe_Cas_ZeroNode*,
                                             Machine_allocateClassObject(ty,
                                                                         NUMBER_OF_ARGUMENTS,
                                                                         ARGUMENTS));
  return self;
}

static void
Mkx_Scribe_Cas_ZeroNode_constructClass
  (
    Mkx_Scribe_Cas_ZeroNode_Class* self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node *(*)(Mkx_Scribe_Cas_Node*,Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node *(*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
