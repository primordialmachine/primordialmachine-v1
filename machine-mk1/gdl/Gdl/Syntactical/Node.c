/// @file Gdl/Syntactical/Node.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gdl/Syntactical/Node.h"

static void Machine_Gdl_Node_visit(Machine_Gdl_Node* self);

static void Machine_Gdl_Node_construct(Machine_Gdl_Node* self, size_t numberOfArguments,
                                       Machine_Value const* arguments);

MACHINE_DEFINE_CLASSTYPE(Machine_Gdl_Node, Machine_Object, &Machine_Gdl_Node_visit,
                         &Machine_Gdl_Node_construct, NULL, NULL, NULL)

static void Machine_Gdl_Node_visit(Machine_Gdl_Node* self) {
  if (self->children) {
    Machine_Gc_visit(self->children);
  }
  if (self->text) {
    Machine_Gc_visit(self->text);
  }
}

static void Machine_Gdl_Node_construct(Machine_Gdl_Node* self, size_t numberOfArguments,
                                       Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->kind = Machine_Value_getInteger(&(arguments[0]));
  self->text = Machine_Value_getString(&(arguments[1]));
  self->children = (Machine_List*)Machine_ArrayList_create();
  self->parent = NULL;
  Machine_setClassType((Machine_Object*)self, Machine_Gdl_Node_getType());
}

Machine_Gdl_Node* Machine_Gdl_Node_create(Machine_Gdl_NodeKind kind, Ring2_String* text) {
  Machine_ClassType* ty = Machine_Gdl_Node_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Machine_Value ARGUMENTS[2];
  Machine_Value_setInteger(&(ARGUMENTS[0]), kind);
  Machine_Value_setString(&(ARGUMENTS[1]), text);
  Machine_Gdl_Node* self
      = (Machine_Gdl_Node*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
