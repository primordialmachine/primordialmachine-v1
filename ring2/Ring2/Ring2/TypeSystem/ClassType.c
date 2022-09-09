// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem/ClassType.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/TypeSystem/ClassType.h"

#include "Ring2/TypeSystem/EnumerationType.h"
#include "Ring2/TypeSystem/InterfaceType.h"
#include "Ring2/Gc.h"
#include "Ring2/JumpTarget.h"
#include "Ring1/Memory.h"
#include "Ring1/Status.h"

static void Machine_ClassType_finalize(void *gc, Machine_ClassType* self) {
  if (self->parent) {
    Ring2_Gc_unlock(self->parent);
  }
  if (self->class.data) {
    Ring1_Memory_deallocate(self->class.data);
    self->class.data = NULL;
  }
  if (self->interfaces.implementationsInitialized) {
    for (size_t i = 0, n = self->interfaces.implementations2.size; i < n; ++i) {
      Machine_InterfaceImplementation const* element
          = Ring1_InlineArray_getAt(&self->interfaces.implementations2, i);
      Ring2_Gc_unlock(element->interfaceType);
    }
    Ring1_InlineArray_uninitialize(&self->interfaces.implementations2);
  }
  if (self->interfaces.dispatchesInitialized) {
    for (size_t i = 0, n = self->interfaces.dispatches2.size; i < n; ++i) {
      Machine_InterfaceDispatchNode const* element
          = Ring1_InlineArray_getAt(&self->interfaces.dispatches2, i);
      Ring2_Gc_unlock(element->dispatch->type);
    }
    Ring1_InlineArray_uninitialize(&self->interfaces.dispatches2);
  }
  Ring2_Type_finalize((Machine_Type*)self);
}

static void Machine_ClassType_visit(void *gc, Machine_ClassType* self) {
  Ring2_Type_visit((Machine_Type*)self);
}

Machine_ClassType* Machine_createClassType(Machine_CreateClassTypeArgs* args) {
  static Ring2_Gc_Type const gcType = {
    .finalize = (Ring2_Gc_FinalizeCallback*)&Machine_ClassType_finalize,
    .visit = (Ring2_Gc_VisitCallback*)&Machine_ClassType_visit,
  };
  Machine_ClassType* classType = Ring2_ObjectModule_allocate(Ring2_Gc_get(), sizeof(Machine_ClassType), &gcType);
  if (!classType) {
    Ring2_jump();
  }

  if (args->parent) {
    if (args->parent->object.size > args->object.size) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
    if (args->parent->class.size > args->class.size) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
  }

  ((Machine_Type*)classType)->flags = Ring2_TypeFlags_Class;
  ((Machine_Type*)classType)->typeRemoved = args->createTypeArgs.typeRemoved;
  ((Machine_Type*)classType)->children.elements = NULL;
  if (Ring1_Memory_allocateArray((void **) & (((Machine_Type*)classType)->children.elements), 0,
                                 sizeof(Machine_Type*))) {
    Ring2_jump();
  }
  // @todo Error handling.
  ((Machine_Type*)classType)->children.size = 0;
  classType->object.size = args->object.size;
  classType->object.visit = args->object.visit;
  classType->object.construct = args->object.construct;
  classType->object.destruct = args->object.destruct;
  classType->parent = args->parent;
  classType->class.size = args->class.size;
  classType->class.construct = args->class.construct;

  classType->interfaces.implementInterfaces = args->interfaces.implementInterfaces;

  static const Ring1_InlineArrayDispatch implementationsConfiguration = {
    .elementSize = sizeof(Machine_InterfaceImplementation),
  };
  if (Ring1_InlineArray_initialize(&classType->interfaces.implementations2,
                                   &implementationsConfiguration)) {
    Ring2_jump();
  }
  classType->interfaces.implementationsInitialized = true;

  static const Ring1_InlineArrayDispatch dispatchesConfiguration = {
    .elementSize = sizeof(Machine_InterfaceDispatchNode),
  };
  if (Ring1_InlineArray_initialize(&classType->interfaces.dispatches2,
                                   &dispatchesConfiguration)) {
    Ring2_jump();
  }
  classType->interfaces.dispatchesInitialized = true;

  if (args->parent) {
    Ring2_Gc_lock(classType->parent);
  }

  return classType;
}

void Machine_ClassType_implement(Machine_ClassType* self, Machine_InterfaceType* interfaceType,
                                 Machine_InterfaceConstructCallback* constructInterface) {
  if (NULL == self) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (NULL == interfaceType) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  for (size_t i = 0, n = self->interfaces.implementations2.size; i < n; ++i) {
    if (((Machine_InterfaceImplementation*)Ring1_InlineArray_getAt(
             &self->interfaces.implementations2, i))
            ->interfaceType
        == interfaceType) {
      Ring1_Status_set(Ring1_Status_InvalidOperation);
      Ring2_jump();
    }
  }
  Machine_InterfaceImplementation temporary
      = { .constructInterface = constructInterface, .interfaceType = interfaceType };
  if (Ring1_InlineArray_append(&self->interfaces.implementations2, &temporary)) {
    Ring2_jump();
  }
  Ring2_Gc_lock(interfaceType);
}

/// @param create @a true create the dispatch if it does not exist, @a false otherwise.
/// @param dispatchNode [out] A pointer to a Machine_InterfaceDispatchNode * variable or a null pointer.
/// @return @a true if the implementation already was created. @a false otherwise.
static bool getOrCreateImplementation(Machine_ClassType* self, Machine_InterfaceType* type,
                                      bool create, Machine_InterfaceDispatchNode** dispatchNode) {
  for (size_t j = 0, m = self->interfaces.dispatches2.size; j < m; ++j) {
    Machine_InterfaceDispatchNode* dispatchNode0
        = Ring1_InlineArray_getAt(&(self->interfaces.dispatches2), j);
    if ((Machine_InterfaceType*)dispatchNode0->dispatch->type == type) {
      *dispatchNode = dispatchNode0;
      return false;
    }
  }
  if (!create) {
    *dispatchNode = NULL;
    return false;
  }
  Machine_InterfaceDispatchNode temporary = { .dispatch = NULL };
  if (Ring1_Memory_allocate(&temporary.dispatch, type->size)) {
    Ring2_jump();
  }
  if (Ring1_InlineArray_append(&(self->interfaces.dispatches2), &temporary)) {
    Ring1_Memory_deallocate(temporary.dispatch);
    Ring2_jump();
  }
  *dispatchNode = Ring1_InlineArray_getAt(&(self->interfaces.dispatches2),
                                          self->interfaces.dispatches2.size - 1);
  Ring2_Gc_lock(type);
  return true;
}

void Machine_ClassType_ensureInitialized(Machine_ClassType* self) {
  if (Ring2_TypeFlag_isSet((Machine_Type*)self, Ring2_TypeFlags_Initialized)) {
    return;
  }

  // Can be invoked any number of times.
  if (self->parent) {
    Machine_ClassType_ensureInitialized(self->parent);
  }

  // ALLOCATE CLASS DISPATCH.
  // Can be invoked any number of times.
  if (!self->class.data) {
    self->class.data = NULL;
    if (Ring1_Memory_allocate(&self->class.data, self->class.size)) {
      Ring2_jump();
    }
    Ring1_Memory_zeroFill(self->class.data, self->class.size);
    if (self->parent) {
      Ring1_Memory_copyFast(self->class.data, self->parent->class.data, self->parent->class.size);
    }
  }

  // INITIALIZE CLASS DISPATCH.
  // Can be invoked any number of times.
  if (self->class.construct) {
    self->class.construct(self->class.data);
  }

  // Can be invoked any number of times.
  // @todo Can it?
  if (self->interfaces.implementInterfaces) {
    self->interfaces.implementInterfaces(self);
  }

  // Initialize interface dispatches.
  if (self->parent) {
    for (size_t i = 0, n = self->parent->interfaces.dispatches2.size; i < n; ++i) {
      Machine_InterfaceDispatchNode* oldDispatch
          = Ring1_InlineArray_getAt(&(self->parent->interfaces.dispatches2), i);
      Machine_InterfaceDispatchNode* newDispatch = NULL;
      if (getOrCreateImplementation(self, (Machine_InterfaceType*)oldDispatch->dispatch->type, true,
                                    &newDispatch)) {
        Ring1_Memory_copyFast(newDispatch->dispatch, oldDispatch->dispatch,
                              ((Machine_InterfaceType*)oldDispatch->dispatch->type)->size);
        Ring2_Gc_lock(newDispatch->dispatch->type);
      }
    }
  }

  // Initialize interface dispatches.
  for (size_t i = 0, n = self->interfaces.implementations2.size; i < n; ++i) {
    Machine_InterfaceImplementation* implementation
        = Ring1_InlineArray_getAt(&(self->interfaces.implementations2), i);
    Machine_InterfaceDispatchNode* dispatch = NULL;
    getOrCreateImplementation(self, implementation->interfaceType, true, &dispatch);
    dispatch->dispatch->type = (Machine_Type*)implementation->interfaceType;
    implementation->constructInterface(dispatch->dispatch);
  }

  Ring2_TypeFlag_set((Machine_Type*)self, Ring2_TypeFlags_Initialized);
}

Machine_ClassType* Machine_ClassType_getParent(Machine_ClassType* self) {
  return self->parent;
}

void* Machine_ClassType_getDispatch(Machine_ClassType* self) {
  return self->class.data;
}

void* Machine_ClassType_getInterfaceDispatch(Machine_ClassType* self,
                                             Machine_InterfaceType* interfaceType) {
  for (size_t i = 0, n = self->interfaces.dispatches2.size; i < n; ++i) {
    Machine_InterfaceDispatchNode* dispatchNode
        = Ring1_InlineArray_getAt(&(self->interfaces.dispatches2), i);
    if ((Machine_InterfaceType*)dispatchNode->dispatch->type == interfaceType) {
      return dispatchNode->dispatch;
    }
  }
  return NULL;
}
