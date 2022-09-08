// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Object.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Types/Object.h"

#include "Ring1/Memory.h"
#include "Ring1/Status.h"
#include <assert.h>

static void Machine_Gc_preMarkCallback(Ring2_Gc* gc, void* context);
static void Machine_Gc_sweepCallback(Ring2_Gc* gc, void* context, Ring2_Gc_SweepStatistics *statistics);

static Ring2_Gc_Tag* g_objects = NULL;

static Ring2_Gc_PreMarkCallbackId g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;
static Ring2_Gc_SweepCallbackId g_sweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;

Ring1_CheckReturn() Ring1_Result
Ring2_ObjectModule_startup
  (
  )
{
  if (Ring2_Gc_startup()) {
    return Ring1_Result_Failure;
  }
  g_preMarkCallbackId = Ring2_Gc_addPreMarkCallback(Ring2_Gc_get(), NULL, &Machine_Gc_preMarkCallback);
  if (g_preMarkCallbackId == Ring2_Gc_PreMarkCallbackId_Invalid) {
    Ring2_Gc_shutdown();
    return Ring1_Result_Failure;
  }
  g_sweepCallbackId = Ring2_Gc_addSweepCallback(Ring2_Gc_get(), NULL, &Machine_Gc_sweepCallback);
  if (g_sweepCallbackId == Ring2_Gc_SweepCallbackId_Invalid) {
    Ring2_Gc_shutdown();
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

void 
Ring2_ObjectModule_shutdown
  (
  )
{ Ring2_Gc_shutdown(); }

void *
Ring2_ObjectModule_allocate
  (
    Ring2_Gc *gc,
    size_t size,
    Ring2_Gc_Type const *type
  )
{ return Ring2_Gc_allocate(gc, size, type, &g_objects); }

static void Machine_Gc_preMarkCallback(Ring2_Gc *gc, void *context) {
  for (Ring2_Gc_Tag* object = g_objects; NULL != object; object = object->objectNext) {
    Ring2_Gc_Tag_setWhite(object);
    if (Ring2_Gc_Tag_getLockCount(object) > 0) {
      Ring2_Gc_visit(Ring2_Gc_get(), Ring2_Gc_toAddress(object));
    }
  }
}

static void Machine_Gc_sweepCallback(Ring2_Gc *gc, void* context, Ring2_Gc_SweepStatistics *statistics) {
  Ring2_Gc_Tag **previous = &g_objects, *current = g_objects;
  while (current) {
    if (Ring2_Gc_Tag_isWhite(current)) {
      // Remove object from list.
      Ring2_Gc_Tag* tag = current;
      *previous = current->objectNext;
      current = current->objectNext;
      // Finalize.
      if (tag->type) {
        if (tag->type && tag->type->finalize) {
          tag->type->finalize(Ring2_Gc_get(), Ring2_Gc_toAddress(tag));
        }
      }
      // Notify weak reference.
      Ring2_Gc_Tag_notifyWeakReferences(tag);
      // Deallocate.
      Ring2_Gc_Tag_uninitialize(tag);
      Ring1_Memory_deallocate(tag);
      if (statistics) {
        statistics->dead++;
      }
    } else {
      Ring2_Gc_Tag_setWhite(current);
      previous = &current->objectNext;
      current = current->objectNext;
      if (statistics) {
        statistics->live++;
      }
    }
  }
}

#include "Ring1/Hash.h"
#include "Ring2/_Include.h"
#include <assert.h>

static Ring2_Integer Machine_Object_getHashValueImpl(Ring2_Context *context, Machine_Object const* self) {
  int64_t temporary;
  Ring1_Hash_toI64_p(&temporary, self);
  return temporary;
}

static Ring2_Boolean Machine_Object_isEqualToImpl(Ring2_Context *context, Machine_Object const* self,
                                                  Ring2_Value const* other) {
  if (!Ring2_Value_isObject(other)) {
    return false;
  }
  return self == Ring2_Value_getObject(other);
}

static Ring2_String* Machine_Object_toStringImpl(Ring2_Context *context, Machine_Object const* self) {
  static_assert(INTPTR_MAX <= Ring2_Integer_Greatest,
                "Machine_Integer can not represent an identity value");
  static_assert(INTPTR_MIN >= Ring2_Integer_Least,
                "Machine_Integer can not represent an identity value");
  return Ring2_Integer_toString(context, (Ring2_Integer)(intptr_t)self);
}

static void Machine_Object_constructClass(Machine_Object_Class* self) {
  self->getHashValue = &Machine_Object_getHashValueImpl;
  self->isEqualTo = &Machine_Object_isEqualToImpl;
  self->toString = &Machine_Object_toStringImpl;
}

static Machine_ClassType* g_Machine_Object_ClassType = NULL;
static void Machine_Object_onTypeDestroyed() {
  g_Machine_Object_ClassType = NULL;
}

Machine_ClassType* Machine_Object_getType() {
  if (!g_Machine_Object_ClassType) {
    Machine_CreateClassTypeArgs args = {
      .createTypeArgs = {
        .typeRemoved = (Machine_TypeRemovedCallback*)&Machine_Object_onTypeDestroyed,
      },
      .parent = NULL,
      .object.size = sizeof(Machine_Object),
      .object.visit = (Machine_ClassObjectVisitCallback*)NULL,
      .object.construct = (Machine_ClassObjectConstructCallback*)&Machine_Object_construct,
      .object.destruct = (Machine_ClassObjectDestructCallback*)NULL,
      .class.size = sizeof(Machine_Object_Class),
      .class.construct = (Machine_ClassConstructCallback*)&Machine_Object_constructClass,
    };
    g_Machine_Object_ClassType = Machine_createClassType(&args);
  }
  return g_Machine_Object_ClassType;
}

void Machine_Object_construct(Machine_Object* self, size_t numberOfArguments,
                              Ring2_Value const* arguments) {
  Ring2_assertNotNull(self);
  Machine_setClassType(self, Machine_Object_getType());
}

static void Machine_ClassObject_visit(void *gc, void* self) {
  Machine_Object* object = (Machine_Object*)self;
  Machine_ClassType *classType = object->classType;
  while (classType) {
    if (classType->object.visit) {
      classType->object.visit(self);
    }
    classType = classType->parent;
  }
}

static void Machine_ClassObject_finalize(void *gc, void* self) {
  Machine_Object* object = (Machine_Object *)self;
  Machine_ClassType* classType = object->classType;
  while (classType) {
    if (classType->object.destruct) {
      classType->object.destruct(self);
    }
    classType = classType->parent;
  }
  // NOW release the class type.
  Ring2_Gc_unlock(object->classType);
}

void Machine_setClassType(Machine_Object* object, Machine_ClassType* classType) {
  assert(object != NULL);
  assert(classType != NULL);

  Machine_Type_ensureInitialized((Machine_Type*)classType);

  if (classType) {
    Ring2_Gc_lock(classType);
  }
  if (object->classType) {
    Ring2_Gc_unlock(object->classType);
  }
  object->classType = classType;
}

Machine_ClassType* Machine_getClassType(Machine_Object* object) {
  return object->classType;
}

Machine_Object* Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments,
                                            Ring2_Value const* arguments) {
  static Ring2_Gc_Type const gcType = {
    .finalize = (Ring2_Gc_FinalizeCallback*)&Machine_ClassObject_finalize,
    .visit = (Ring2_Gc_VisitCallback*)&Machine_ClassObject_visit,
  };
  Machine_Object *o = Ring2_ObjectModule_allocate(Ring2_Gc_get(), type->object.size, &gcType);
  if (!o) {
    Ring2_jump();
  }
  Ring2_Gc_Tag* t = Ring2_Gc_toTag(o);
  o->classType = type;
  Ring2_Gc_lock(o->classType);
  type->object.construct((Machine_Object*)o, numberOfArguments, arguments);
  return o;
}

Ring2_Integer Machine_Object_getHashValue(Ring2_Context* context, Machine_Object const* self) {
  MACHINE_VIRTUALCALL_IMPL(Machine_Object, getHashValue, return, context, self);
}

Ring2_Boolean Machine_Object_isEqualTo(Ring2_Context* context, Machine_Object const* self, Ring2_Value const* other) {
  MACHINE_VIRTUALCALL_IMPL(Machine_Object, isEqualTo, return, context, self, other);
}

Ring2_String* Machine_Object_toString(Ring2_Context* context, Machine_Object const* self) {
  MACHINE_VIRTUALCALL_IMPL(Machine_Object, toString, return, context, self);
}
