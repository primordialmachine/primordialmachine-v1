#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/PointerArray.h"
#include "Runtime/List.h"

#include <malloc.h>
#include <memory.h>


#define Machine_PointerArray_MaximalCapacity SIZE_MAX / sizeof(void *)

static void Machine_PointerArray_visit(Machine_PointerArray* self);

static void Machine_PointerArray_construct(Machine_PointerArray* self, size_t numberOfArguments, const Machine_Value* arguments);

static void Machine_PointerArray_destruct(Machine_PointerArray* self);

struct Machine_PointerArray {
  Machine_Object parent;
  Machine_List* list;
};

MACHINE_DEFINE_CLASSTYPE_EX(Machine_PointerArray, Machine_Object, &Machine_PointerArray_visit, &Machine_PointerArray_construct, &Machine_PointerArray_destruct)

static void Machine_PointerArray_visit(Machine_PointerArray* self) {
  if (self->list) {
    Machine_visit(self->list);
  }
}

static void Machine_PointerArray_constructClass(Machine_PointerArray_Class *self)
{/*Intentionally empty.*/}

static void Machine_PointerArray_construct(Machine_PointerArray* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->list = Machine_List_create();
  Machine_PointerArray_constructClass(self);
  Machine_setClassType((Machine_Object*)self, Machine_PointerArray_getClassType());
}

static void Machine_PointerArray_destruct(Machine_PointerArray* self)
{/*Intentionally empty.*/}

Machine_PointerArray* Machine_PointerArray_create() {
  Machine_ClassType* ty = Machine_PointerArray_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
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
      Machine_setStatus(Machine_Status_InvalidOperation);
      Machine_jump();
    }
    return NULL;
  }
  return Machine_Value_getObject(&v);
}

size_t Machine_PointerArray_getSize(Machine_PointerArray* self) {
  if (!self){
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  return Machine_Collection_getSize((Machine_Collection*)self->list);
}

void Machine_PointerArray_prepend(Machine_PointerArray* self, void* pointer) {
  Machine_PointerArray_insert(self, 0, pointer);
}

void Machine_PointerArray_append(Machine_PointerArray* self, void* pointer) {
  MACHINE_ASSERT_NOTNULL(self);
  if (!pointer) {
    Machine_Value v;
    Machine_Value_setVoid(&v, Machine_Void_Void);
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
    Machine_Value_setVoid(&v, Machine_Void_Void);
    Machine_List_insertAt(self->list, index, v);
  }
  else {
    Machine_Value v;
    Machine_Value_setObject(&v, pointer);
    Machine_List_insertAt(self->list, index, v);
  }
}
