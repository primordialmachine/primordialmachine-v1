/// @file Mkx/Scribe/Cas/Nodes/UnaryMinusNode.c
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#include "Mkx/Scribe/Cas/Nodes/GroupNode.h"

#include "Mkx/Scribe/Cas/Nodes.h"
#include "Mkx/Scribe/Cas/EmissionContext.h"
#include "Mkx/Scribe/Cas/EvaluationContext.h"


static void
Mkx_Scribe_Cas_GroupNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_GroupNode* self
  );

static void
Mkx_Scribe_Cas_GroupNode_constructClass
  (
    Mkx_Scribe_Cas_GroupNode_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_GroupNode,
                         Mkx_Scribe_Cas_Node,
                         &Mkx_Scribe_Cas_GroupNode_visit,
                         &Mkx_Scribe_Cas_GroupNode_construct,
                         NULL,
                         &Mkx_Scribe_Cas_GroupNode_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_GroupNode_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_GroupNode* self
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
  if (!node)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Mkx_Scribe_Cas_NodeKind_Group != Mkx_Scribe_Cas_Node_getKind(node))
  {
    Ring1_Log_error("%s:%d: invalid argument type\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  Mkx_Scribe_Cas_GroupNode* groupNode = Ring1_cast(Mkx_Scribe_Cas_GroupNode*, node);
  if (!groupNode->operand)
  {
    Ring1_Log_error("%s:%d: invalid argument\n", __FILE__, __LINE__);
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
}

static Mkx_Scribe_Cas_GroupNode*
clone
  (
    Mkx_Scribe_Cas_GroupNode* self
  )
{ return Mkx_Scribe_Cas_GroupNode_create(self->operand ? Mkx_Scribe_Cas_Node_clone(self->operand) : NULL); }

static void
emit
  (
    Mkx_Scribe_Cas_GroupNode *self,
    Mkx_Scribe_Cas_EmissionContext *emissionContext
  )
{
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));
  Ring2_String* leftParenthesis = Ring2_String_fromC(false, "(");
  Ring2_String* rightParenthesis = Ring2_String_fromC(false, ")");

  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(leftParenthesis)));
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, self->operand);
  Mkx_Scribe_Cas_EmissionContext_emit(emissionContext, Ring1_cast(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_OutputNode_create(rightParenthesis)));
}

static Mkx_Scribe_Cas_Node*
evaluate
  (
    Mkx_Scribe_Cas_GroupNode* self,
    Mkx_Scribe_Cas_EvaluationContext* evaluationContext
  )
{
  static const bool OPTIMIZE = true;
  
  check(Ring1_cast(Mkx_Scribe_Cas_Node*, self));

  if (OPTIMIZE)
  {
    // "(-e)" reduces to "-e".
    if (Mkx_Scribe_Cas_NodeKind_UnaryMinus == Mkx_Scribe_Cas_Node_getKind(self->operand))
    {
      return self->operand;
    }
    // "(e)" reduces to "e" if "e" is a variable or an index.
    if (Mkx_Scribe_Cas_NodeKind_Variable == Mkx_Scribe_Cas_Node_getKind(self->operand) ||
        Mkx_Scribe_Cas_NodeKind_Index1d == Mkx_Scribe_Cas_Node_getKind(self->operand) ||
        Mkx_Scribe_Cas_NodeKind_Index2d == Mkx_Scribe_Cas_Node_getKind(self->operand))
    {
      return self->operand;
    }
    // "((e))" reduces to "(e)".
    if (Mkx_Scribe_Cas_NodeKind_Group == Mkx_Scribe_Cas_Node_getKind(self->operand))
    {
      return self->operand;
    }
    // "(0)" reduces to "0".
    // "(1)" reduces to "1".
    else if (Mkx_Scribe_Cas_NodeKind_One == Mkx_Scribe_Cas_Node_getKind(self->operand) ||
             Mkx_Scribe_Cas_NodeKind_Zero == Mkx_Scribe_Cas_Node_getKind(self->operand))
    {
      return self->operand;
    }
    else
    {
      return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
    }
  }
  else
  {
    return Ring1_cast(Mkx_Scribe_Cas_Node*, self);
  }
}

static int64_t
getNumberOfChildren
  (
    Mkx_Scribe_Cas_GroupNode* self
  )
{ return 1; }

static Mkx_Scribe_Cas_Node*
getChildAt
  (
    Mkx_Scribe_Cas_GroupNode* self,
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
    Mkx_Scribe_Cas_GroupNode* self,
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
Mkx_Scribe_Cas_GroupNode_construct
  (
    Mkx_Scribe_Cas_GroupNode* self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Mkx_Scribe_Cas_Node_construct(Ring1_cast(Mkx_Scribe_Cas_Node*, self), numberOfArguments, arguments);
  Ring1_cast(Mkx_Scribe_Cas_Node*, self)->kind = Mkx_Scribe_Cas_NodeKind_Group;
  self->operand = Ring1_cast(Mkx_Scribe_Cas_Node *, Ring2_Value_getObject(&arguments[0]));
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Cas_GroupNode_getType());
}

Mkx_Scribe_Cas_GroupNode *
Mkx_Scribe_Cas_GroupNode_create
  (
    Mkx_Scribe_Cas_Node *operand
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_GroupNode_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*, operand));
  Mkx_Scribe_Cas_GroupNode* self = Ring1_cast(Mkx_Scribe_Cas_GroupNode*,
                                              Machine_allocateClassObject(ty,
                                                                          NUMBER_OF_ARGUMENTS,
                                                                          arguments));
  return self;
}

static void
Mkx_Scribe_Cas_GroupNode_constructClass
  (
    Mkx_Scribe_Cas_GroupNode_Class* self
  )
{ 
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->emit = (void (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EmissionContext*)) & emit;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->evaluate = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, Mkx_Scribe_Cas_EvaluationContext*)) & evaluate;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->clone = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*)) & clone;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getNumberOfChildren = (int64_t (*)(Mkx_Scribe_Cas_Node*)) & getNumberOfChildren;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->getChildAt = (Mkx_Scribe_Cas_Node * (*)(Mkx_Scribe_Cas_Node*, int64_t)) & getChildAt;
  Ring1_cast(Mkx_Scribe_Cas_Node_Class *, self)->setChildAt = (void (*)(Mkx_Scribe_Cas_Node*, int64_t, Mkx_Scribe_Cas_Node*)) & setChildAt;
}
