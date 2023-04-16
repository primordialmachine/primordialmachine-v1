// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Environment/Variable.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Environment/Variable.h"

struct Mkx_Scribe_Variable_Class {
  Machine_Object_Class _parent;
};

struct Mkx_Scribe_Variable {
  Machine_Object _parent;
  Ring2_String* name;
  Ring2_Value value;
};

static void
Mkx_Scribe_Variable_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Variable* self
  );

static void
Mkx_Scribe_Variable_constructClass
  (
    Mkx_Scribe_Variable_Class *self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Variable,
                         Machine_Object,
                         &Mkx_Scribe_Variable_visit,
                         &Mkx_Scribe_Variable_construct,
                         NULL,
                         &Mkx_Scribe_Variable_constructClass,
                         NULL)

static void
Mkx_Scribe_Variable_visit
  (
    Ring2_Gc *gc,
    Mkx_Scribe_Variable* self
  )
{
  if (self->name) {
    Ring2_Gc_visit(gc, self->name);
  }
  Ring2_Value_visit(gc, &self->value);
}

static void
Mkx_Scribe_Variable_constructClass
  (
    Mkx_Scribe_Variable_Class *self
  )
{ }

void
Mkx_Scribe_Variable_construct
  (
    Mkx_Scribe_Variable *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->name = Ring2_Value_getString(&arguments[0]);
  Ring2_Value_setVoid(&self->value, Ring2_Void_Void);
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Variable_getType());
}

Mkx_Scribe_Variable*
Mkx_Scribe_Variable_create
  (
    Ring2_String* name
  )
{
  Machine_Type* ty = Mkx_Scribe_Variable_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setString(&arguments[0], name);
  Mkx_Scribe_Variable *self = Ring1_cast(Mkx_Scribe_Variable*,
                                         Machine_allocateClassObject(ty,
                                                                     NUMBER_OF_ARGUMENTS,
                                                                     arguments));
  return self;
}

Ring2_String*
Mkx_Scribe_Variable_getName
  (
    Mkx_Scribe_Variable* self
  )
{ return self->name; }

Ring2_Integer
Mkx_Scribe_Variable_getIntegerValue
  (
    Mkx_Scribe_Variable* self
  )
{
  if (!Ring2_Value_isInteger(&self->value))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "variable not of type integer\n"));
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getInteger(&self->value);
}

void
Mkx_Scribe_Variable_setIntegerValue
  (
    Mkx_Scribe_Variable* self,
    Ring2_Integer value
  )
{ Ring2_Value_setInteger(&self->value, value); }

bool
Mkx_Scribe_Variable_isIntegerValue
  (
    Mkx_Scribe_Variable* self
  )
{ return Ring2_Value_isInteger(&self->value); }

Ring2_String*
Mkx_Scribe_Variable_getStringValue
  (
    Mkx_Scribe_Variable* self
  )
{
  if (!Ring2_Value_isString(&self->value))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "variable not of type string\n"));
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getString(&self->value);
}

void
Mkx_Scribe_Variable_setStringValue
  (
    Mkx_Scribe_Variable *self,
    Ring2_String* value
  )
{ Ring2_Value_setString(&self->value, value); }

bool
Mkx_Scribe_Variable_isStringValue
  (
    Mkx_Scribe_Variable* self
  )
{ return Ring2_Value_isString(&self->value); }

Ring2_ForeignProcedure*
Mkx_Scribe_Variable_getForeignFunctionValue
  (
    Mkx_Scribe_Variable* self
  )
{
  if (!Ring2_Value_isForeignProcedure(&self->value))
  {
    Ring2_emitf(Ring2_Context_get(), Ring2_String_fromC(false, "variable not of type foreign function\n"));
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getForeignProcedure(&self->value);
}

void
Mkx_Scribe_Variable_setForeignFunctionValue
  (
    Mkx_Scribe_Variable* self,
    Ring2_ForeignProcedure* value
  )
{ Ring2_Value_setForeignProcedure(&self->value, value); }

bool
Mkx_Scribe_Variable_isForeignFunctionValue
  (
    Mkx_Scribe_Variable* self
  )
{ return Ring2_Value_isForeignProcedure(&self->value); }

Ring2_Value
Mkx_Scribe_Variable_get
  (
    Mkx_Scribe_Variable* self
  )
{ return self->value; }

void
Mkx_Scribe_Variable_set
  (
    Mkx_Scribe_Variable* self,
    Ring2_Value value
  )
{ Ring2_Value_set(&self->value, &value); }
