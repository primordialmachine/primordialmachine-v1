/// @file Mkx/Scribe/Cas/Nodes/BinaryPlusNode.h
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/OutputNode.h"


#include "Ring1/Log.h"
#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_OutputNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_OutputNode* self
  );

static void
Mkx_Scribe_Cas_OutputNode_constructClass
  (
    Mkx_Scribe_Cas_OutputNode_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_OutputNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_OutputNode_visit,
                         &Mkx_Scribe_Cas_OutputNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_OutputNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_OutputNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_OutputNode* self
  )
{
  if (self->string) {
    Ring2_Gc_visit(gc, self->string);
  }
}

static void
check
  (
    Mkx_Scribe_Cas_Node* node
  )
{
  if (!node)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_Output != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_OutputNode*
clone
  (
    Mkx_Scribe_Cas_OutputNode *self
  )
{ return Mkx_Scribe_Cas_OutputNode_create(self->string); }

static void
emit
  (
    Mkx_Scribe_Cas_OutputNode* self,
    Mkx_Scribe_Cas_EmissionContext* emissionContext
  )
{ check(Ring1_cast(Mkx_Scribe_Cas_Node*, self)); }

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_OutputNode* self
  )
{ return 0; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_OutputNode* self,
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
    Mkx_Scribe_Cas_OutputNode* self,
    int64_t index,
    Mkx_Scribe_Cas_Node* node
  )
{
  Ring1_Log_error("%s:%d: index out of bounds\n", __FILE__, __LINE__);
  Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
  Ring2_jump();
}

void
Mkx_Scribe_Cas_OutputNode_construct
  (
    Mkx_Scribe_Cas_OutputNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_Output;
  self->string = Ring2_Value_getString(&arguments[0]);
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_OutputNode_getType());
}

Mkx_Scribe_Cas_OutputNode*
Mkx_Scribe_Cas_OutputNode_create
  (
    Ring2_String* string
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_OutputNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setString(&arguments[0], string);
  Mkx_Scribe_Cas_OutputNode* self = Ring1_cast(Mkx_Scribe_Cas_OutputNode*,
                                               Machine_allocateClassObject(ty,
                                                                           NUMBER_OF_ARGUMENTS,
                                                                           arguments));
  return self;
}

static void
Mkx_Scribe_Cas_OutputNode_constructClass
  (
    Mkx_Scribe_Cas_OutputNode_Class* self
  )
{
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
