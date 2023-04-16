// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Environment/Environment.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Mkx/Scribe/Environment/Environment.h"


#include "Ring2/Operations.h"
#include "Mkx/Scribe/Environment/Variable.h"


struct Mkx_Scribe_Environment_Class {
  Machine_Object_Class _parent;
};

struct Mkx_Scribe_Environment {
  Machine_Object _parent;
  /// @brief Pointer to the enclosing environment or a null pointer.
  Mkx_Scribe_Environment* enclosing;
  Ring2_Collections_HashMap* hashMap;
};

static void
Mkx_Scribe_Environment_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Environment* self
  );

static void
Mkx_Scribe_Environment_constructClass
  (
    Mkx_Scribe_Environment_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Mkx_Scribe_Environment,
                         Machine_Object,
                         &Mkx_Scribe_Environment_visit,
                         &Mkx_Scribe_Environment_construct,
                         NULL,
                         &Mkx_Scribe_Environment_constructClass,
                         NULL)

static void
Mkx_Scribe_Environment_visit
  (
    Ring2_Gc* gc,
    Mkx_Scribe_Environment* self
  )
{
  if (self->enclosing) {
    Ring2_Gc_visit(gc, self->enclosing);
  }
  if (self->hashMap) {
    Ring2_Gc_visit(gc, self->hashMap);
  }
}

static void
Mkx_Scribe_Environment_constructClass
  (
    Mkx_Scribe_Environment_Class* self
  )
{ }

void
Mkx_Scribe_Environment_construct
  (
    Mkx_Scribe_Environment* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->enclosing = NULL;
  self->hashMap = Ring2_Collections_HashMap_create();
  Machine_setClassType((Machine_Object*)self, Mkx_Scribe_Environment_getType());
}

Mkx_Scribe_Environment*
Mkx_Scribe_Environment_create
  (
  )
{
  Machine_Type* ty = Mkx_Scribe_Environment_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = {Ring2_Value_StaticInitializerVoid()};
  Mkx_Scribe_Environment *self = Ring1_cast(Mkx_Scribe_Environment*,
                                            Machine_allocateClassObject(ty,
                                                                        NUMBER_OF_ARGUMENTS,
                                                                        ARGUMENTS));
  return self;
}

Mkx_Scribe_Variable*
Mkx_Scribe_Environment_get
  (
    Mkx_Scribe_Environment* self,
    Ring2_String* name
  )
{
  Ring2_Value k;
  Ring2_Value_setString(&k, name);
  Ring2_Value v = Ring2_Collections_Map_get(Ring1_cast(Ring2_Collections_Map *, self->hashMap), k);
  if (!Ring2_Value_isObject(&v)) {
    return NULL;
  }
  return Ring1_cast(Mkx_Scribe_Variable*, Ring2_Value_getObject(&v));
}

Mkx_Scribe_Variable*
Mkx_Scribe_Environment_getRecursive
  (
    Mkx_Scribe_Environment* self,
    Ring2_String* name
  )
{
  Mkx_Scribe_Environment* current = self;
  while (current)
  {
    Mkx_Scribe_Variable *variable = Mkx_Scribe_Environment_get(current, name);
    if (variable) return variable;
    current = current->enclosing;
  }
  return NULL;
}

void
Mkx_Scribe_Environment_set
  (
    Mkx_Scribe_Environment* env,
    Mkx_Scribe_Variable* var
  )
{
  Ring2_Value k;
  Ring2_Value_setString(&k, Mkx_Scribe_Variable_getName(var));
  Ring2_Value v;
  Ring2_Value_setObject(&v, Ring1_cast(Machine_Object *, var));
  Ring2_Collections_Map_set(Ring1_cast(Ring2_Collections_Map *, env->hashMap), k, v);
}

void
Mkx_Scribe_Environment_setAll
  (
    Mkx_Scribe_Environment* self,
    Mkx_Scribe_Environment* other
  )
{
  if (self == other) {
    return;
  }
  Ring2_Collections_List* sourceEntries = Ring2_Collections_Map_toList(Ring1_cast(Ring2_Collections_Map *, other->hashMap));
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection *, sourceEntries)); i < n; ++i) {
    Ring2_Value sourceEntryValue = Ring2_Collections_List_getAt(sourceEntries, i);
    if (!Ring2_Value_isObject(&sourceEntryValue)) { 
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    Machine_Object* sourceObject = (Machine_Object *)Ring2_Value_getObject(&sourceEntryValue);
    if (!Machine_Type_isSubTypeOf((Machine_Type *)sourceObject->classType, (Machine_Type *)Ring2_Collections_Pair_getType())) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();   
    }
    Ring2_Collections_Pair* sourcePair = (Ring2_Collections_Pair*)sourceObject;
    Ring2_Value k = Ring2_Collections_Pair_get(sourcePair, 0),
                v = Ring2_Collections_Pair_get(sourcePair, 1);
    Ring2_Collections_Map_set(Ring1_cast(Ring2_Collections_Map *, self->hashMap), k, v);
  }
}

Mkx_Scribe_Environment *
Mkx_Scribe_Environment_getEnclosing
  (
    Mkx_Scribe_Environment* self
  )
{ return self->enclosing; }

void
Mkx_Scribe_Environment_setEnclosing
  (
    Mkx_Scribe_Environment* self,
    Mkx_Scribe_Environment* enclosing
  )
{
  self->enclosing = enclosing;
}
