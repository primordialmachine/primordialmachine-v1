#include "Runtime/List.h"


#include <malloc.h>
#include <memory.h>


static void append(Machine_List* self, Machine_Value value);

static void prepend(Machine_List* self, Machine_Value value);

static void Machine_List_visit(Machine_List* self);

static void Machine_List_destruct(Machine_List* self);

static void Machine_List_construct(Machine_List* self, size_t numberOfArguments, const Machine_Value* arguments) {
  self->append = &append;
  self->prepend = &prepend;
  Machine_setClassType(self, Machine_List_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_List)

Machine_ClassType* Machine_List_getClassType() {
  if (!g_Machine_List_ClassType) {
    g_Machine_List_ClassType =
      Machine_createClassType
        (
          Machine_Collection_getClassType(),
          sizeof(Machine_List),
          (Machine_ClassTypeRemovedCallback*)&Machine_List_onTypeDestroyed,
          (Machine_ClassObjectVisitCallback*)&Machine_List_visit,
          (Machine_ClassObjectConstructCallback*)&Machine_List_construct,
          (Machine_ClassObjectDestructCallback*)&Machine_List_destruct
        );
  }
  return g_Machine_List_ClassType;
}

static void append(Machine_List* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_List_insert(self, Machine_Collection_getSize((Machine_Collection *)self), value);
}

static void prepend(Machine_List* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_List_insert(self, 0, value);
}

static void Machine_List_visit(Machine_List* self)
{/*Intentionally empty.*/}


static void Machine_List_destruct(Machine_List* self)
{/*Intentionally empty.*/}

Machine_List* Machine_List_create() {
  Machine_ClassType* ty = Machine_List_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
  Machine_List* self = (Machine_List*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Value Machine_List_getAt(Machine_List* self, size_t index) {
  MACHINE_ASSERT_NOTNULL(self);
  return self->getAt(self, index);
}

void Machine_List_prepend(Machine_List* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  self->prepend(self, value);
}

void Machine_List_append(Machine_List* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  self->append(self, value);
}

void Machine_List_insert(Machine_List* self, size_t index, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  self->insert(self, index, value);
}
