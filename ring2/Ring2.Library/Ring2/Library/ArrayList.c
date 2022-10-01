// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ArrayList.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/ArrayList.h"
#undef RING2_LIBRARY_PRIVATE


#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Collection.h"
#include "Ring2/Library/CollectionUtilities.h"
#include "Ring2/Library/List.h"
#undef RING2_LIBRARY_PRIVATE
#include <stdio.h>


struct Machine_ArrayList_Class {
  Machine_Object_Class _parent;
};

struct Machine_ArrayList {
  Machine_Object _parent;
  Ring2_Value* values;
  int64_t size, capacity;
};

static void
Machine_ArrayList_destruct
  (
    Machine_ArrayList* self
  );

static void
Machine_ArrayList_visit
  (
    Machine_ArrayList* self
  );

// >>

static void
append
  (
    Machine_ArrayList* self,
    Ring2_Value value
  );

// Ring2.Collection
static void
clear
  (
    Machine_ArrayList* self
  );

// Ring2.Collection
static int64_t
getSize
  (
    Machine_ArrayList const* self
  );

// Ring2.Collection
static bool
isEmpty
  (
    Machine_ArrayList const* self
  );

static Ring2_Value
getAt
  (
    Machine_ArrayList const* self,
    int64_t index
  );

static void
insertAt
  (
    Machine_ArrayList* self,
    int64_t index,
    Ring2_Value value
  );

static void
prepend
  (
    Machine_ArrayList* self,
    Ring2_Value value
  );

static void
removeAt
  (
    Machine_ArrayList* self,
    int64_t index
  );

static void
removeAtFast
  (
    Machine_ArrayList* self,
    int64_t index
  );

static void
implement_Machine_Collection
  (
    Machine_Collection_Dispatch* self
  );

static void
implement_Machine_List
  (
    Machine_List_Dispatch* self
  );

static void
implementInterfaces
  (
    Machine_ClassType* self
  );

// <<

MACHINE_DEFINE_CLASSTYPE(Machine_ArrayList,
                         Machine_Object,
                         &Machine_ArrayList_visit,
                         &Machine_ArrayList_construct,
                         &Machine_ArrayList_destruct,
                         NULL,
                         &implementInterfaces)

// >>

static void
append
  (
    Machine_ArrayList* self,
    Ring2_Value value
  )
{ CollectionUtilities_insertAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, value, self->size); }

// Ring2.Collection
static void
clear
  (
    Machine_ArrayList* self
  )
{ self->size = 0; }

// Ring2.Collection
static int64_t
getSize
  (
    Machine_ArrayList const* self
  )
{ return self->size; }

// Ring2.Collection
static bool
isEmpty
  (
    Machine_ArrayList const* self
  )
{ return 0 == self->size; }

static Ring2_Value
getAt
  (
    Machine_ArrayList const* self,
    int64_t index 
  )
{
  if (index < 0 || index >= self->size) {
    fprintf(stderr, "index out of bounds");
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return *(self->values + index);
}

static void
insertAt
  (
    Machine_ArrayList* self,
    int64_t index,
    Ring2_Value value
  )
{ CollectionUtilities_insertAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, value, index); }

static void
prepend
  (
    Machine_ArrayList* self,
    Ring2_Value value
  )
{ CollectionUtilities_insertAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, value, 0); }

static void
removeAt
  (
    Machine_ArrayList* self,
    int64_t index 
  )
{ CollectionUtilities_removeAt(Ring2_Context_get(), &self->values, &self->size, &self->capacity, index); }

static void
removeAtFast
  (
    Machine_ArrayList* self,
    int64_t index 
  )
{ CollectionUtilities_removeAtFast(Ring2_Context_get(), &self->values, &self->size, &self->capacity, index); }

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
implement_Machine_List
  (
    Machine_List_Dispatch* self
  )
{
  self->append = (void (*)(Machine_List *, Ring2_Value)) & append;
  self->getAt = (Ring2_Value(*)(Machine_List const *, int64_t index)) & getAt;
  self->insertAt = (void (*)(Machine_List*, int64_t, Ring2_Value)) & insertAt;
  self->prepend = (void (*)(Machine_List *, Ring2_Value)) & prepend;
  self->removeAt = (void (*)(Machine_List*, int64_t)) & removeAt;
  self->removeAtFast = (void (*)(Machine_List*, int64_t)) & removeAtFast;
}

static void 
implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Machine_Collection_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Machine_Collection);
  Machine_ClassType_implement(self, Machine_List_getType(),
                              (Machine_InterfaceConstructCallback*)&implement_Machine_List);
}

// <<

static void
grow
  (
    Ring2_Context* context,
    Machine_ArrayList* self,
    int64_t required
  )
{ CollectionUtilities_grow(context, &self->values, &self->size, &self->capacity, required); }

static void
ensureFreeCapacity
  (
    Ring2_Context* context,
    Machine_ArrayList* self,
    int64_t required
  )
{ CollectionUtilities_ensureFreeCapacity(context, &self->values, &self->size, &self->capacity, required); }

static void
Machine_ArrayList_destruct
  (
    Machine_ArrayList *self
  )
{
  if (self->values) {
    Ring1_Memory_deallocate(self->values);
    self->values = NULL;
  }
}

static void
Machine_ArrayList_visit
  (
    Machine_ArrayList *self
  )
{
  if (self->values) {
    Ring2_Gc* gc = Ring2_Gc_get();
    for (int64_t i = 0, n = self->size; i < n; ++i) {
      Ring2_Value_visit(gc, self->values + i);
    }
  }
}

void
Machine_ArrayList_construct
  (
    Machine_ArrayList *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->size = 0;
  self->capacity = MIN_CAPACITY;
  self->values = NULL;
  if (Ring1_Memory_allocateArray(&self->values, (size_t)self->capacity, sizeof(Ring2_Value))) {
    fprintf(stderr, "allocation failed");
    Ring2_jump();
  }
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_ArrayList_getType());
}

Machine_ArrayList*
Machine_ArrayList_create
  (
  )
{
  Machine_ClassType* ty = Machine_ArrayList_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[1] = { Ring2_Value_StaticInitializerVoid() };
  Machine_ArrayList* self = (Machine_ArrayList*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
