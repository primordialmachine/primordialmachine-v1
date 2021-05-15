#include "Runtime/PointerArray.h"


#include <malloc.h>
#include <memory.h>


#define Machine_PointerArray_MaximalCapacity SIZE_MAX / sizeof(void *)

struct Machine_PointerArray {
  void** elements;
  size_t size, capacity;
};

static void Machine_PointerArray_visit(Machine_PointerArray* self) {
  if (self->elements) {
    for (size_t i = 0, n = self->size; i < n; ++i) {
      void *element = self->elements[i];
      if (element) {
        Machine_visit(element);
      }
    }
  }
}

static void Machine_PointerArray_construct(Machine_PointerArray* self, size_t numberOfArguments, const Machine_Value* arguments) {
  self->elements = NULL;
  self->size = 0;
  self->capacity = 0;
}

static void Machine_PointerArray_destruct(Machine_PointerArray* self) {
  if (self->elements) {
    free(self->elements);
    self->elements = NULL;
  }
}

MACHINE_DEFINE_CLASSTYPE(Machine_PointerArray)

Machine_ClassType* Machine_PointerArray_getClassType() {
  if (!g_Machine_PointerArray_ClassType) {
    g_Machine_PointerArray_ClassType =
      Machine_createClassType
        (
          NULL,
          sizeof(Machine_PointerArray),
          (Machine_ClassTypeRemovedCallback*)&Machine_PointerArray_onTypeDestroyed,
          (Machine_ClassObjectVisitCallback*)&Machine_PointerArray_visit,
          (Machine_ClassObjectConstructCallback*)&Machine_PointerArray_construct,
          (Machine_ClassObjectDestructCallback*)&Machine_PointerArray_destruct
        );
  }
  return g_Machine_PointerArray_ClassType;
}

Machine_PointerArray* Machine_PointerArray_create() {
  Machine_ClassType* ty = Machine_PointerArray_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
  Machine_PointerArray* self = (Machine_PointerArray *)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_PointerArray_clear(Machine_PointerArray* self) {
  self->size = 0;
}

void *Machine_PointerArray_getAt(Machine_PointerArray* self, size_t index) {
  if (!self){
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if (index >= self->size) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  return self->elements[index];
}

size_t Machine_PointerArray_getSize(Machine_PointerArray* self) {
  if (!self){
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  return self->size;
}

void Machine_PointerArray_prepend(Machine_PointerArray* self, void* pointer) {
  Machine_PointerArray_insert(self, 0, pointer);
}

void Machine_PointerArray_append(Machine_PointerArray* self, void* pointer) {
  if (!self) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_PointerArray_insert(self, self->size, pointer);
}

void Machine_PointerArray_insert(Machine_PointerArray* self, size_t index, void *pointer) {
  if (!self) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if ((self->capacity - self->size) == 0) {
    if (self->capacity == Machine_PointerArray_MaximalCapacity) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    size_t newCapacity = self->capacity + 1;
    void *newElements = realloc(self->elements, sizeof(void*) * newCapacity);
    if (!newElements) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->elements = newElements;
    self->capacity = newCapacity;
  }
  if (index < self->size) {
    memmove(self->elements + index + 1, self->elements + index + 0, sizeof(void *) * (self->size - index));
  }
  self->elements[index] = pointer;
  self->size++;
}
