// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Object.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Types/Object.h"
#undef RING2_PRIVATE


#include "Ring1/All/_Include.h"
#include "Ring1/Hash.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#define RING2_PRIVATE (1)
#include "Ring2/Assert.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Operations/Integer.h"
#include "Ring2/Types/Value.h"
#include "Ring2/TypeSystem/ClassType.h"
#undef RING2_PRIVATE


static Ring1_CheckReturn() Ring1_Result
Ring2_ObjectModule_startup
  (
  );

static void
Ring2_ObjectModule_shutdown
  (
  );

/*PREMARK*/ static void
Mkx_Interpreter_ObjectHeap_preMark
  (
    Ring2_Gc* gc,
    void* context
  );

/*SWEEP*/ static void
Mkx_Interpreter_ObjectHeap_sweep
  (
    Ring2_Gc* gc,
    void* context,
    Ring2_Gc_SweepStatistics* statistics
  );

// List of objects.
static Ring2_Gc_Tag* g_objects;

/// @brief The type of an object heap.
typedef struct Mkx_Interpreter_ObjectHeap Mkx_Interpreter_ObjectHeap;

static Mkx_Interpreter_ObjectHeap*
Mkx_Interpreter_ObjectHeap_create
  (
  );

static void
Mkx_Interpreter_ObjectHeap_destroy
  (
    Mkx_Interpreter_ObjectHeap* objectHeap
  );

struct Mkx_Interpreter_ObjectHeap {
  Ring1_Memory_ModuleHandle memoryModuleHandle;
  Ring2_Gc_Tag *objects;
};

static Mkx_Interpreter_ObjectHeap* g_objectHeap = NULL;

static Ring2_Gc_PreMarkCallbackId g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;

static Ring2_Gc_SweepCallbackId g_sweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;

static Ring1_CheckReturn() Ring1_Result
Ring2_ObjectModule_startup
  (
  )
{
  assert(NULL == g_objectHeap);
  g_objectHeap = Mkx_Interpreter_ObjectHeap_create();
  if (!g_objectHeap) {
    return Ring1_Result_Failure;
  }
  g_preMarkCallbackId = Ring2_Gc_addPreMarkCallback(Ring2_Gc_get(), NULL,
                                                    (Ring2_Gc_PreMarkCallback*)&Mkx_Interpreter_ObjectHeap_preMark);
  if (!g_preMarkCallbackId) {
    Mkx_Interpreter_ObjectHeap_destroy(g_objectHeap);
    g_objectHeap = NULL;
    
    return Ring1_Result_Failure;
  }

  g_sweepCallbackId = Ring2_Gc_addSweepCallback(Ring2_Gc_get(), NULL,
                                                (Ring2_Gc_SweepCallback*)& Mkx_Interpreter_ObjectHeap_sweep);
  if (!g_sweepCallbackId) {
    Ring2_Gc_removePreMarkCallback(Ring2_Gc_get(), g_preMarkCallbackId);
    g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;

    Mkx_Interpreter_ObjectHeap_destroy(g_objectHeap);
    g_objectHeap = NULL;
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
Ring2_ObjectModule_shutdown
  (
  )
{
  assert(Ring2_Gc_SweepCallbackId_Invalid != g_sweepCallbackId);
  Ring2_Gc_removeSweepCallback(Ring2_Gc_get(), g_sweepCallbackId);
  g_sweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;

  assert(Ring2_Gc_PreMarkCallbackId_Invalid != g_preMarkCallbackId);
  Ring2_Gc_removePreMarkCallback(Ring2_Gc_get(), g_preMarkCallbackId);
  g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;

  assert(NULL != g_objectHeap);
  Mkx_Interpreter_ObjectHeap_destroy(g_objectHeap);
  g_objectHeap = NULL;
}

Ring1_Module_Define(Ring2, ObjectModule, Ring2_ObjectModule_startup, Ring2_ObjectModule_shutdown)

static Mkx_Interpreter_ObjectHeap*
Mkx_Interpreter_ObjectHeap_create
  (
  )
{
  Ring1_Memory_ModuleHandle handle = Ring1_Memory_ModuleHandle_acquire();
  if (!handle) {
    return NULL;
  }
  Mkx_Interpreter_ObjectHeap* objectHeap;
  if (Ring1_Memory_allocate(&objectHeap, sizeof(Mkx_Interpreter_ObjectHeap))) {
    Ring1_Memory_ModuleHandle_relinquish(handle);
    return NULL;
  }
  objectHeap->objects = NULL;
  objectHeap->memoryModuleHandle = handle;
  return objectHeap;
}

static void
Mkx_Interpreter_ObjectHeap_destroy
  (
    Mkx_Interpreter_ObjectHeap *objectHeap
  )
{
  Ring1_Memory_ModuleHandle handle = objectHeap->memoryModuleHandle;
  objectHeap->objects = NULL;
  Ring1_Memory_deallocate(objectHeap);
  Ring1_Memory_ModuleHandle_relinquish(handle);
}

/*PREMARK*/ void
Mkx_Interpreter_ObjectHeap_preMark
  (
    Ring2_Gc* gc,
    void* context
  )
{
  Ring2_Gc_Tag* current = g_objectHeap->objects;
  while (current) {
    if (Ring2_Gc_Tag_getLockCount(current) > 0) {
      Ring2_Gc_visit(gc, Ring2_Gc_toAddress(current));
    }
    current = current->objectNext;
  }
}

/*SWEEP*/ void
Mkx_Interpreter_ObjectHeap_sweep
  (
    Ring2_Gc* gc,
    void* context,
    Ring2_Gc_SweepStatistics* statistics
  )
{
  statistics->dead = 0;
  statistics->live = 0;
  Ring2_Gc_Tag** previous = &(g_objectHeap->objects),
               * current = g_objectHeap->objects;
  while (current) {
    if (Ring2_Gc_Tag_isWhite(current)) {
      Ring2_Gc_Tag* object = current;
      *previous = current->objectNext;
      current = current->objectNext;
      Ring2_Gc_Tag_notifyWeakReferences(object);
      if (object->type->finalize) {
        object->type->finalize(gc, Ring2_Gc_toAddress(object));
      }
      Ring1_Memory_deallocate(object);
      statistics->dead++;
    } else {
      Ring2_Gc_Tag_setWhite(current);
      previous = &current->objectNext;
      current = current->objectNext;
      statistics->live++;
    }
  }
}

static Ring1_CheckReturn() Ring2_Integer
Machine_Object_getHashValueImpl
  (
    Ring2_Context* context,
    Machine_Object const* self
  )
{
  int64_t temporary;
  Ring1_Hash_toI64_p(&temporary, self);
  return temporary;
}

static Ring1_CheckReturn() Ring2_Boolean
Machine_Object_isEqualToImpl
  (
    Ring2_Context* context,
    Machine_Object const* self,
    Ring2_Value const* other
  )
{
  if (!Ring2_Value_isObject(other)) {
    return false;
  }
  return self == (Machine_Object *)Ring2_Value_getObject(other);
}

static Ring1_CheckReturn() Ring2_Boolean
Machine_Object_isNotEqualToImpl
  (
    Ring2_Context* context,
    Machine_Object const* self,
    Ring2_Value const* other
  )
{
  if (!Ring2_Value_isObject(other)) {
    return true;
  }
  return self != (Machine_Object *)Ring2_Value_getObject(other);
}

static Ring1_CheckReturn() Ring2_String*
Machine_Object_toStringImpl
  (
    Ring2_Context* context,
    Machine_Object const* self
  )
{
  static_assert(INTPTR_MAX <= Ring2_Integer_Greatest,
                "Machine_Integer can not represent an identity value");
  static_assert(INTPTR_MIN >= Ring2_Integer_Least,
                "Machine_Integer can not represent an identity value");
  return Ring2_Integer_toString(context, (Ring2_Integer)(intptr_t)self);
}

static void Machine_Object_constructClass(Machine_Object_Class* self) {
  self->getHashValue = &Machine_Object_getHashValueImpl;
  self->isEqualTo = &Machine_Object_isEqualToImpl;
  self->isNotEqualTo = &Machine_Object_isNotEqualToImpl;
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

Machine_Object*
Machine_allocateClassObject
  (
    Machine_ClassType* type,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  static const Ring2_Gc_Type TYPE = {
    .finalize = &Machine_ClassObject_finalize,
    .visit = &Machine_ClassObject_visit,
  };
  Machine_Object *object = Ring2_Gc_allocate(Ring2_Gc_get(),
                                             (size_t) type->object.size,
                                             &TYPE, 
                                             &g_objectHeap->objects);
  if (Ring1_Unlikely(!object)) {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  Ring2_Gc_Tag* t = Ring2_Gc_toTag(object);
  object->classType = type;
  Ring2_Gc_lock(object->classType);
  type->object.construct(object, numberOfArguments, arguments);
  return object;
}

Ring1_CheckReturn() Ring2_Integer
Machine_Object_getHashValue
  (
    Ring2_Context* context,
    Machine_Object const* self
  )
{ MACHINE_VIRTUALCALL_IMPL(Machine_Object, getHashValue, return, context, self); }

Ring1_CheckReturn() Ring2_Boolean
Machine_Object_isEqualTo
  (
    Ring2_Context* context,
    Machine_Object const* self,
    Ring2_Value const* other
  )
{ MACHINE_VIRTUALCALL_IMPL(Machine_Object, isEqualTo, return, context, self, other); }

Ring1_CheckReturn() Ring2_Boolean
Machine_Object_isNotEqualTo
  (
    Ring2_Context* context,
    Machine_Object const* self,
    Ring2_Value const* other
  )
{ MACHINE_VIRTUALCALL_IMPL(Machine_Object, isNotEqualTo, return, context, self, other); }

Ring1_CheckReturn() Ring2_String*
Machine_Object_toString
  (
    Ring2_Context* context,
    Machine_Object const* self
  )
{ MACHINE_VIRTUALCALL_IMPL(Machine_Object, toString, return, context, self); }
