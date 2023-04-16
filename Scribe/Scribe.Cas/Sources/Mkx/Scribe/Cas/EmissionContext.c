// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Cas/EmissionContext.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Cas/EmissionContext.h"

#include "Mkx/Scribe/Cas/Nodes.h"


static void
Mkx_Scribe_Cas_EmissionContext_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Cas_EmissionContext* self
  );

static void
Mkx_Scribe_Cas_EmissionContext_constructClass
  (
    Mkx_Scribe_Cas_EmissionContext_Class* self
  );

static bool
isEmpty
  (
    Ring2_Collections_Stack* stack
  );

/// @brief Short-hand function to pop a node.
static Mkx_Scribe_Cas_Node*
popNode
  (
    Ring2_Collections_Stack* stack
  );

/// @brief Short-hand function to push a node.
static void
pushNode
  (
    Ring2_Collections_Stack* stack,
    Mkx_Scribe_Cas_Node* node
  );

/// @brief Short-hand function to determine if a node is an output node.
static bool
isOutputNode
  (
    Mkx_Scribe_Cas_Node* node
  );

static void
reduce
  (
    Mkx_Scribe_Cas_EmissionContext* self
  );

static void
emit
  (
    Mkx_Scribe_Cas_EmissionContext* self,
    Mkx_Scribe_Cas_Node* node
  );

static void
reset
  (
    Mkx_Scribe_Cas_EmissionContext* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Cas_EmissionContext, Machine_Object,
                         &Mkx_Scribe_Cas_EmissionContext_visit,
                         &Mkx_Scribe_Cas_EmissionContext_construct,
                         NULL,
                         &Mkx_Scribe_Cas_EmissionContext_constructClass,
                         NULL)

static void
Mkx_Scribe_Cas_EmissionContext_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Cas_EmissionContext *self
  )
{
  if (self->inputStack)
  {
    Ring2_Gc_visit(gc, self->inputStack);
  }
  if (self->outputStack)
  {
    Ring2_Gc_visit(gc, self->outputStack);
  }
  if (self->outputStringBuffer)
  {
    Ring2_Gc_visit(gc, self->outputStringBuffer);
  }
}

static void
Mkx_Scribe_Cas_EmissionContext_constructClass
  (
    Mkx_Scribe_Cas_EmissionContext_Class* self
  )
{
  self->emit = &emit;
  self->reduce = &reduce;
  self->reset = &reset;
}

void
Mkx_Scribe_Cas_EmissionContext_construct
  (
    Mkx_Scribe_Cas_EmissionContext *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->outputStringBuffer = Ring2_StringBuffer_create(Ring2_Context_get());
  self->inputStack = Ring1_cast(Ring2_Collections_Stack *, Ring2_Collections_ArrayStack_create(Ring2_Context_get()));
  self->outputStack = Ring1_cast(Ring2_Collections_Stack *, Ring2_Collections_ArrayStack_create(Ring2_Context_get()));
  self->indexEmissionOption = Mkx_Scribe_Cas_IndexEmissionOption_Hll;
  self->matrixEmissionOption = Mkx_Scribe_Cas_MatrixEmissionOption_RowDelimiters;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Mkx_Scribe_Cas_EmissionContext_getType());
}

Mkx_Scribe_Cas_EmissionContext*
Mkx_Scribe_Cas_EmissionContext_create
  (
  )
{
  Machine_Type* ty = Mkx_Scribe_Cas_EmissionContext_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Mkx_Scribe_Cas_EmissionContext *self = Ring1_cast(Mkx_Scribe_Cas_EmissionContext*,
                                                    Machine_allocateClassObject(ty,
                                                                                NUMBER_OF_ARGUMENTS,
                                                                                ARGUMENTS));
  return self;
}

static bool
isEmpty
  (
    Ring2_Collections_Stack* stack
  )
{ return Ring2_Collections_Collection_isEmpty(Ring1_cast(Ring2_Collections_Collection *, stack)); }

static Mkx_Scribe_Cas_Node *
popNode
  (
    Ring2_Collections_Stack* stack
  )
{
  Ring2_Value value = Ring2_Collections_Stack_pop(stack);
  Mkx_Scribe_Cas_Node* node = Ring1_cast(Mkx_Scribe_Cas_Node*, Ring2_Value_getObject(&value));
  return node;
}

static void
pushNode
  (
    Ring2_Collections_Stack* stack,
    Mkx_Scribe_Cas_Node* node
  )
{
  Ring2_Value value;
  Ring2_Value_setObject(&value, Ring1_cast(Machine_Object *, node));
  Ring2_Collections_Stack_push(stack, value);
}

static bool
isOutputNode
  (
    Mkx_Scribe_Cas_Node *node
  )
{ return Mkx_Scribe_Cas_NodeKind_Output == Mkx_Scribe_Cas_Node_getKind(node); }

static void
reduce
  (
    Mkx_Scribe_Cas_EmissionContext* self
  )
{
  if (self->isReducing) return;
  self->isReducing = true;
  while (!isEmpty(self->inputStack))
  {
    Mkx_Scribe_Cas_Node* node = popNode(self->inputStack);
    if (isOutputNode(node))
    {
      pushNode(self->outputStack, node);
    }
    else
    {
      Mkx_Scribe_Cas_Node_emit(node, self);
    }
  }
  while (!isEmpty(self->outputStack))
  {
    Mkx_Scribe_Cas_Node* node = popNode(self->outputStack);
    if (!isOutputNode(node))
    {
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "internal error: not an output node\n"));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    Mkx_Scribe_Cas_OutputNode* outputNode = Ring1_cast(Mkx_Scribe_Cas_OutputNode*, node);
    Ring2_StringBuffer_appendString(self->outputStringBuffer, outputNode->string);
  }
  /// @todo Handle exception and set isReducing to false in exception handler.
  self->isReducing = false;
}

static void
emit
  (
    Mkx_Scribe_Cas_EmissionContext* self,
    Mkx_Scribe_Cas_Node* node
  )
{
  pushNode(self->inputStack, node);
  Mkx_Scribe_Cas_EmissionContext_reduce(self);
}

static void
reset
  (
    Mkx_Scribe_Cas_EmissionContext* self
  )
{
  Ring2_Collections_Collection_clear(Ring1_cast(Ring2_Collections_Collection *, self->inputStack));
  Ring2_Collections_Collection_clear(Ring1_cast(Ring2_Collections_Collection *, self->outputStack));
  Ring2_StringBuffer_clear(self->outputStringBuffer);
}

void
Mkx_Scribe_Cas_EmissionContext_reduce
  (
    Mkx_Scribe_Cas_EmissionContext* self
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Scribe_Cas_EmissionContext, reduce, , self); }

void
Mkx_Scribe_Cas_EmissionContext_emit
  (
    Mkx_Scribe_Cas_EmissionContext* self,
    Mkx_Scribe_Cas_Node* node
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Scribe_Cas_EmissionContext, emit, , self, node); }

void
Mkx_Scribe_Cas_EmissionContext_reset
  (
    Mkx_Scribe_Cas_EmissionContext* self
  )
{ MACHINE_VIRTUALCALL_IMPL(Mkx_Scribe_Cas_EmissionContext, reset, , self); }
