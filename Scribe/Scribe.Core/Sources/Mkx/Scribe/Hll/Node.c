// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Hll/Node.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Hll/Node.h"


static void
Mkx_Scribe_Hll_Node_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Hll_Node* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Hll_Node, Machine_Object, &Mkx_Scribe_Hll_Node_visit, &Mkx_Scribe_Hll_Node_construct,
                         NULL, NULL, NULL)

static void
Mkx_Scribe_Hll_Node_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Hll_Node* self
  )
{
  if (self->children) {
    Ring2_Gc_visit(gc, self->children);
  }
  if (self->position) {
    Ring2_Gc_visit(gc, self->position);
  }
}

void
Mkx_Scribe_Hll_Node_construct
  (
    Mkx_Scribe_Hll_Node *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->kind = (Mkx_Scribe_Hll_NodeKind)Ring2_Value_getInteger(&arguments[0]);
  self->position = (Mkx_Scribe_Position *)Ring2_Value_getObject(&arguments[1]);
  self->children = NULL;
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Hll_Node_getType());
}

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_create
  (
    Mkx_Scribe_Hll_NodeKind kind,
    Mkx_Scribe_Position* position
  )
{
  Machine_Type* ty = Mkx_Scribe_Hll_Node_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid(),
                              Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&arguments[0], Ring1_cast(Ring2_Integer,kind));
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,position));
  Mkx_Scribe_Hll_Node *self = Ring1_cast(Mkx_Scribe_Hll_Node*,
                                         Machine_allocateClassObject(ty,
                                                                     NUMBER_OF_ARGUMENTS,
                                                                     arguments));
  return self;
}

Mkx_Scribe_Position*
Mkx_Scribe_Hll_Node_getPosition
  (
    Mkx_Scribe_Hll_Node* self
  )
{ return self->position; }

Mkx_Scribe_Hll_NodeKind
Mkx_Scribe_Hll_Node_getKind
  (
    Mkx_Scribe_Hll_Node* self
  )
{ return self->kind; }

int64_t
Mkx_Scribe_Hll_Node_getNumberOfChildren
  (
    Mkx_Scribe_Hll_Node* self
  )
{
  if (!self->children) return 0;
  else return Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection *, self->children));
}

Mkx_Scribe_Hll_Node*
Mkx_Scribe_Hll_Node_getChildAt
  (
    Mkx_Scribe_Hll_Node* self,
    int64_t index
  )
{
  if (!self->children)
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "index out of bounds\n"));
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  else
  {
    Ring2_Value value = Ring2_Collections_List_getAt(Ring1_cast(Ring2_Collections_List *, self->children), index);
    if (!Ring2_Value_isObject(&value))
    {
      Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "element is not an object\n"));
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring1_cast(Mkx_Scribe_Hll_Node*, Ring2_Value_getObject(&value));
  }
}

void
Mkx_Scribe_Hll_Node_append
  (
    Mkx_Scribe_Hll_Node* self,
    Mkx_Scribe_Hll_Node* element
  )
{
  if (self == element || NULL == element) {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "invalid argument\n"));
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (!self->children) {
    self->children = Ring1_cast(Ring2_Collections_List *, Ring2_Collections_ArrayList_create(Ring2_Context_get()));
  }
  Ring2_Value value;
  Ring2_Value_setObject(&value, Ring1_cast(Machine_Object *, element));
  Ring2_Collections_List_append(Ring1_cast(Ring2_Collections_List *, self->children), value);
}

void
Mkx_Scribe_Hll_Node_prependChild
  (
    Mkx_Scribe_Hll_Node* self,
    Mkx_Scribe_Hll_Node* node
  )
{
  Ring2_Value value;
  Ring2_Value_setObject(&value, Ring1_cast(Machine_Object *, node));
  Ring2_Collections_List_prepend(Ring1_cast(Ring2_Collections_List *, self->children), value);
}

void
Mkx_Scribe_Hll_Node_insertChildAt
  (
    Mkx_Scribe_Hll_Node* self,
    int64_t index,
    Mkx_Scribe_Hll_Node* node
  )
{
  Ring2_Value value;
  Ring2_Value_setObject(&value, Ring1_cast(Machine_Object *, node));
  Ring2_Collections_List_insertAt(Ring1_cast(Ring2_Collections_List *, self->children), index, value);
}
