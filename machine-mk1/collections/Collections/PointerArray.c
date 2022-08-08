/// @file Collections/PointerArray.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/PointerArray.h"

#include "Collections/ArrayList.h"
#include "Collections/Collection.h"
#include "Collections/List.h"

static void Machine_PointerArray_visit(Machine_PointerArray* self);

static void Machine_PointerArray_construct(Machine_PointerArray* self, size_t numberOfArguments, Machine_Value const* arguments);

static void Machine_PointerArray_destruct(Machine_PointerArray* self);

struct Machine_PointerArray_Class {
  Machine_Object_Class __parent;
};

struct Machine_PointerArray {
  Machine_Object __parent;

  Machine_List* list;
};

MACHINE_DEFINE_CLASSTYPE(Machine_PointerArray, Machine_Object, &Machine_PointerArray_visit,
                         &Machine_PointerArray_construct, &Machine_PointerArray_destruct, NULL,
                         NULL)

static void Machine_PointerArray_visit(Machine_PointerArray* self) {
  if (self->list) {
    Machine_Gc_visit(self->list);
  }
}

static void Machine_PointerArray_construct(Machine_PointerArray* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->list = (Machine_List *)Machine_ArrayList_create();
  Machine_setClassType((Machine_Object*)self, Machine_PointerArray_getType());
}

static void Machine_PointerArray_destruct(Machine_PointerArray* self)
{/*Intentionally empty.*/}

Machine_PointerArray* Machine_PointerArray_create() {
  Machine_ClassType* ty = Machine_PointerArray_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_PointerArray* self = (Machine_PointerArray *)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_PointerArray_clear(Machine_PointerArray* self) {
  Machine_Collection_clear((Machine_Collection *)self->list);
}

void *Machine_PointerArray_getAt(Machine_PointerArray* self, size_t index) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_Value v = Machine_List_getAt(self->list, index);
  if (!Machine_Value_isObject(&v)) {
    if (!Machine_Value_isVoid(&v)) {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
    return NULL;
  }
  return Machine_Value_getObject(&v);
}

size_t Machine_PointerArray_getSize(Machine_PointerArray* self) {
  MACHINE_ASSERT_NOTNULL(self);
  return Machine_Collection_getSize((Machine_Collection*)self->list);
}

void Machine_PointerArray_prepend(Machine_PointerArray* self, void* pointer) {
  Machine_PointerArray_insert(self, 0, pointer);
}

void Machine_PointerArray_append(Machine_PointerArray* self, void* pointer) {
  MACHINE_ASSERT_NOTNULL(self);
  if (!pointer) {
    Machine_Value v;
    Machine_Value_setVoid(&v, Ring2_Void_Void);
    Machine_List_append(self->list, v);
  } else {
    Machine_Value v;
    Machine_Value_setObject(&v, pointer);
    Machine_List_append(self->list, v);
  }
}

void Machine_PointerArray_insert(Machine_PointerArray* self, size_t index, void *pointer) {
  MACHINE_ASSERT_NOTNULL(self);
  if (!pointer) {
    Machine_Value v;
    Machine_Value_setVoid(&v, Ring2_Void_Void);
    Machine_List_insertAt(self->list, index, v);
  }
  else {
    Machine_Value v;
    Machine_Value_setObject(&v, pointer);
    Machine_List_insertAt(self->list, index, v);
  }
}
