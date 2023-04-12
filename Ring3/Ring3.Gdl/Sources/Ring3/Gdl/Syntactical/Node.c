/// @file Ring3/Gdl/Syntactical/Node.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Syntactical/Node.h"
#undef RING3_GDL_PRIVATE


#include "Ring1/All/_Include.h"


static void
Machine_Gdl_Node_visit
  (
    Machine_Gdl_Node* self
  );

static void
Machine_Gdl_Node_construct
  (
    Machine_Gdl_Node* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

MACHINE_DEFINE_CLASSTYPE(Machine_Gdl_Node /*type*/,
                         Machine_Object /*parentType*/,
                         &Machine_Gdl_Node_visit /*visit*/,
                         &Machine_Gdl_Node_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

static void
Machine_Gdl_Node_visit
  (
    Machine_Gdl_Node* self
  )
{
  if (self->children) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->children);
  }
  Ring2_Value_visit(Ring2_Gc_get(), &self->value);
}

static void
Machine_Gdl_Node_construct
  (
    Machine_Gdl_Node* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  if (numberOfArguments != 2) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  self->kind = Ring2_Value_getInteger(&(arguments[0]));
  switch (self->kind) {
    case Machine_Gdl_NodeKind_Boolean: {
      // @todo Add and use Ring2_Object_isInstanceOf.
      Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 1,
                                            Ring3_Gdl_BooleanLiteral_getType());
      self->value = arguments[1];
    } break;
    case Machine_Gdl_NodeKind_Integer: {
      // @todo Add and use Ring2_Object_isInstanceOf.
      Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 1,
                                            Ring3_Gdl_IntegerLiteral_getType());
      self->value = arguments[1];
    } break;
    case Machine_Gdl_NodeKind_Real: {
      // @todo Add and use Ring2_Object_isInstanceOf.
      Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 1,
                                            Ring3_Gdl_RealLiteral_getType());
      self->value = arguments[1];
    } break;
    case Machine_Gdl_NodeKind_String: {
      // @todo Add and use Ring2_Object_isInstanceOf.
      Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 1,
                                            Ring3_Gdl_StringLiteral_getType());
      self->value = arguments[1];
    } break;
    case Machine_Gdl_NodeKind_Void: {
      // @todo Add and use Ring2_Object_isInstanceOf.
      Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 1,
                                            Ring3_Gdl_VoidLiteral_getType());
      self->value = arguments[1];
    } break;
    case Machine_Gdl_NodeKind_Name: {
      // @todo Add and use Ring2_Object_isInstanceOf.
      Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 1,
                                            Ring3_Gdl_Name_getType());
      self->value = arguments[1];
    } break;
    case Machine_Gdl_NodeKind_CompilationUnit: {
      // @todo Add and use Ring2_Object_isInstanceOf.
      Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 1);
      self->value = arguments[1];
    } break;
    default: {
      self->value = arguments[1];
    } break;
  };
  self->children = (Ring2_Collections_List*)Ring2_Collections_ArrayList_create();
  self->parent = NULL;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gdl_Node_getType());
}

Ring1_NoDiscardReturn() Machine_Gdl_Node*
Machine_Gdl_Node_create
  (
    Machine_Gdl_NodeKind kind,
    Ring2_Value const* value
  )
{
  Machine_Type* ty = Machine_Gdl_Node_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setInteger(&(arguments[0]), kind);
  arguments[1] = *value;
  Machine_Gdl_Node* self = Ring1_cast(Machine_Gdl_Node*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

void
Machine_Gdl_Node_append
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Node* other
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerObject(Ring1_cast(Machine_Object *, other));
  Ring2_Collections_List_append(self->children, v);
}

void
Machine_Gdl_Node_prepend
  (
    Machine_Gdl_Node* self,
    Machine_Gdl_Node* other
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerObject(Ring1_cast(Machine_Object *, other));
  Ring2_Collections_List_prepend(self->children, v);
}

void
Machine_Gdl_Node_insertAt
  (
    Machine_Gdl_Node* self,
    Ring2_Integer index,
    Machine_Gdl_Node* other
  )
{
  Ring2_Value v = Ring2_Value_StaticInitializerObject(Ring1_cast(Machine_Object *, other));
  Ring2_Collections_List_insertAt(self->children, index, v);
}

Ring1_NoDiscardReturn() Machine_Gdl_Node *
Machine_Gdl_Node_getAt
  (
    Machine_Gdl_Node* self,
    Ring2_Integer index
  )
{
  Ring2_Value temporary = Ring2_Collections_List_getAt(self->children, index);
  return Ring1_cast(Machine_Gdl_Node *, Ring2_Value_getObject(&temporary));
}

Ring1_NoDiscardReturn() int64_t
Machine_Gdl_Node_getSize
  (
    Machine_Gdl_Node* self
  )
{ return Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection *, self->children)); }

Ring1_NoDiscardReturn() Machine_Gdl_NodeKind
Machine_Gdl_Node_getKind
  (
    Machine_Gdl_Node const *self
  )
{ return self->kind; }
