// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Stack.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com).

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/ArrayStack.h"
#undef RING2_LIBRARY_PRIVATE


#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Collection.h"
#include "Ring2/Library/CollectionUtilities.h"
#undef RING2_IBRARY_PRIVATE


struct Machine_ArrayStack_Class {
  Machine_Object_Class _parent;
};

struct Machine_ArrayStack {
  Machine_Object _parent;
  Ring2_Value* values;
  int64_t size, capacity;
};

// Ring2.Collection
static void
clear
  (
    Machine_ArrayStack* self
  );

// Ring2.Collection
static int64_t
getSize
  (
    Machine_ArrayStack const* self
  );

// Ring2.Collection
static bool
isEmpty
  (
    Machine_ArrayStack const* self
  );

static void
grow
  (
    Machine_ArrayStack* self,
    int64_t required
  );

static void
ensureFreeCapacity
  (
    Machine_ArrayStack* self,
    int64_t required
  );

static void
Machine_ArrayStack_destruct
  (
    Machine_ArrayStack* self
  );

static void
Machine_ArrayStack_visit
  (
    Machine_ArrayStack* self
  );

static void
implement_Machine_Collection
  (
    Machine_Collection_Dispatch* self
  );

static void
implementInterfaces
  (
    Machine_ClassType* self
  );

MACHINE_DEFINE_CLASSTYPE(Machine_ArrayStack /*type*/,
                         Machine_Object /*parentType*/,
                         &Machine_ArrayStack_visit /*visit*/,
                         &Machine_ArrayStack_construct /*construct*/,
                         &Machine_ArrayStack_destruct /*destruct*/,
                         NULL /*constructClass*/,
                         &implementInterfaces)

// Ring2.Collection
static void
clear
  (
    Machine_ArrayStack* self
  )
{ self->size = 0; }

// Ring2.Collection
static int64_t
getSize
  (
    Machine_ArrayStack const* self
  )
{ return self->size; }

// Ring2.Collection
static bool
isEmpty
  (
    Machine_ArrayStack const* self
  )
{ return 0 == self->size; }

static void
grow
  (
    Machine_ArrayStack* self,
    int64_t required
  )
{ CollectionUtilities_grow(Ring2_Context_get(), &self->values, &self->size, &self->capacity, required); }

static void
ensureFreeCapacity
  (
    Machine_ArrayStack *self,
    int64_t required
  )
{ CollectionUtilities_ensureFreeCapacity(Ring2_Context_get(), &self->values, &self->size, &self->capacity, required); }

static void
Machine_ArrayStack_destruct
  (
    Machine_ArrayStack *self
  )
{
  if (self->values) {
    Ring1_Memory_deallocate(self->values);
    self->values = NULL;
  }
}

static void
Machine_ArrayStack_visit
  (
    Machine_ArrayStack *self
  )
{
  if (self->values) {
    Ring2_Gc* gc = Ring2_Gc_get();
    for (int64_t i = 0, n = self->size; i < n; ++i) {
      Ring2_Value_visit(gc, self->values + i);
    }
  }
}

static void
implement_Machine_Collection
  (
    Machine_Collection_Dispatch* self
  )
{
  self->clear = (void (*)(Machine_Collection*)) & clear;
  self->getSize = (int64_t (*)(Machine_Collection const*)) & getSize;
  self->isEmpty = (bool (*)(Machine_Collection const*)) & isEmpty;
}

static void
implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Machine_Collection_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Machine_Collection);
}

void
Machine_ArrayStack_construct
  (
    Machine_ArrayStack *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->size = 0;
  self->capacity = MIN_CAPACITY;
  self->values = NULL;
  if (Ring1_Memory_allocateArray(&self->values, (size_t)self->capacity, sizeof(Ring2_Value))) {
    fprintf(stderr, "allocation failed");
    Ring2_jump();
  }
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Machine_ArrayStack_getType());
}

Machine_ArrayStack*
Machine_ArrayStack_create
  (
  )
{
  Machine_ClassType* ty = Machine_ArrayStack_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[1] = { Ring2_Value_StaticInitializerVoid() };
  Machine_ArrayStack* self = (Machine_ArrayStack*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void
Machine_ArrayStack_push
  (
    Machine_ArrayStack* self,
    Ring2_Value value
  )
{
  ensureFreeCapacity(self, 1);
  *(self->values + self->size) = value;
  self->size++;
}

Ring2_Value
Machine_ArrayStack_pop
  (
    Machine_ArrayStack* self
  )
{
  Ring2_Value value = *(self->values + self->size - 1);
  self->size--;
  return value;
}
