/// @file Runtime/Object/ClassType.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Object/ClassType.h"

#include "Ring1/Status.h"
#include "Runtime/Assertions.h"
#include "Runtime/Gc/Gc.h"
#include "Runtime/JumpTargetModule.h"
#include "Runtime/Object/ClassType.module.h"
#include "Runtime/Object/InterfaceType.module.h"
#include "Runtime/Type.module.h"

static void Machine_ClassType_finalize(void *gc, Machine_ClassType* self) {
  if (self->parent) {
    Machine_Gc_unlock(self->parent);
  }
  if (self->class.data) {
    Ring1_Memory_deallocate(self->class.data);
    self->class.data = NULL;
  }
  if (self->interfaces.implementationsInitialized) {
    for (size_t i = 0, n = self->interfaces.implementations2.size; i < n; ++i) {
      Machine_InterfaceImplementation const* element
          = Machine_Eal_InlineArray_getAt(&self->interfaces.implementations2, i);
      Machine_Gc_unlock(element->interfaceType);
    }
    Machine_Eal_InlineArray_uninitialize(&self->interfaces.implementations2);
  }
  if (self->interfaces.dispatchesInitialized) {
    for (size_t i = 0, n = self->interfaces.dispatches2.size; i < n; ++i) {
      Machine_InterfaceDispatchNode const* element
          = Machine_Eal_InlineArray_getAt(&self->interfaces.dispatches2, i);
      Machine_Gc_unlock(element->dispatch->type);
    }
    Machine_Eal_InlineArray_uninitialize(&self->interfaces.dispatches2);
  }
  _Type_finalize((Machine_Type*)self);
}

static void Machine_ClassType_visit(void *gc, Machine_ClassType* self) {
  _Type_visit((Machine_Type*)self);
}

Machine_ClassType* Machine_createClassType(Machine_CreateClassTypeArgs* args) {
  static Ring2_Gc_Type const gcType = {
    .finalize = (Ring2_Gc_FinalizeCallback*)&Machine_ClassType_finalize,
    .visit = (Ring2_Gc_VisitCallback*)&Machine_ClassType_visit,
  };
  Machine_Gc_AllocationArguments const allocationArguments = {
    .prefixSize = 0,
    .suffixSize = sizeof(Machine_ClassType),
    .type = &gcType,
  };

  Machine_ClassType* classType = Machine_Gc_allocate(&allocationArguments);
  if (!classType) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }

  if (args->parent) {
    if (args->parent->object.size > args->object.size) {
      Machine_setStatus(Machine_Status_InvalidArgument);
      Machine_jump();
    }
    if (args->parent->class.size > args->class.size) {
      Machine_setStatus(Machine_Status_InvalidArgument);
      Machine_jump();
    }
  }

  ((Machine_Type*)classType)->flags = Machine_TypeFlags_Class;
  ((Machine_Type*)classType)->typeRemoved = args->createTypeArgs.typeRemoved;
  ((Machine_Type*)classType)->children.elements = NULL;
  if (Ring1_Memory_allocateArray((void **) & (((Machine_Type*)classType)->children.elements), 0,
                                 sizeof(Machine_Type*))) {
    Ring1_Status_set(Ring1_Status_Success);
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
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

  static const Machine_Eal_InlineArrayDispatch implementationsConfiguration = {
    .elementSize = sizeof(Machine_InterfaceImplementation),
  };
  if (Machine_Eal_InlineArray_initialize(&classType->interfaces.implementations2,
                                         &implementationsConfiguration)) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  classType->interfaces.implementationsInitialized = true;

  static const Machine_Eal_InlineArrayDispatch dispatchesConfiguration = {
    .elementSize = sizeof(Machine_InterfaceDispatchNode),
  };
  if (Machine_Eal_InlineArray_initialize(&classType->interfaces.dispatches2,
                                         &dispatchesConfiguration)) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  classType->interfaces.dispatchesInitialized = true;

  if (args->parent) {
    Machine_Gc_lock(classType->parent);
  }

  return classType;
}

void Machine_ClassType_implement(Machine_ClassType* self, Machine_InterfaceType* interfaceType,
                                 Machine_InterfaceConstructCallback* constructInterface) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(interfaceType);
  for (size_t i = 0, n = self->interfaces.implementations2.size; i < n; ++i) {
    if (((Machine_InterfaceImplementation*)Machine_Eal_InlineArray_getAt(
             &self->interfaces.implementations2, i))
            ->interfaceType
        == interfaceType) {
      Machine_setStatus(Machine_Status_InvalidOperation);
      Machine_jump();
    }
  }
  Machine_InterfaceImplementation temporary
      = { .constructInterface = constructInterface, .interfaceType = interfaceType };
  if (Machine_Eal_InlineArray_append(&self->interfaces.implementations2, &temporary)) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_Gc_lock(interfaceType);
}

/// @param create @a true create the dispatch if it does not exist, @a false otherwise.
/// @param dispatchNode [out] A pointer to a Machine_InterfaceDispatchNode * variable or a null pointer.
/// @return @a true if the implementation already was created. @a false otherwise.
static bool getOrCreateImplementation(Machine_ClassType* self, Machine_InterfaceType* type,
                                      bool create, Machine_InterfaceDispatchNode** dispatchNode) {
  for (size_t j = 0, m = self->interfaces.dispatches2.size; j < m; ++j) {
    Machine_InterfaceDispatchNode* dispatchNode0
        = Machine_Eal_InlineArray_getAt(&(self->interfaces.dispatches2), j);
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
    Ring1_Status_set(Ring1_Status_Success);
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  if (Machine_Eal_InlineArray_append(&(self->interfaces.dispatches2), &temporary)) {
    Ring1_Memory_deallocate(temporary.dispatch);
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  *dispatchNode = Machine_Eal_InlineArray_getAt(&(self->interfaces.dispatches2),
                                                self->interfaces.dispatches2.size - 1);
  Machine_Gc_lock(type);
  return true;
}

void Machine_ClassType_ensureInitialized(Machine_ClassType* self) {
  if (_TypeFlag_isSet((Machine_Type*)self, Machine_TypeFlags_Initialized)) {
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
      Ring1_Status_set(Ring1_Status_Success);
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    Ring1_Memory_zeroFill(self->class.data, self->class.size);
    if (self->parent) {
      Machine_Eal_Memory_copy(self->class.data, self->parent->class.data, self->parent->class.size,
                              false);
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
          = Machine_Eal_InlineArray_getAt(&(self->parent->interfaces.dispatches2), i);
      Machine_InterfaceDispatchNode* newDispatch = NULL;
      if (getOrCreateImplementation(self, (Machine_InterfaceType*)oldDispatch->dispatch->type, true,
                                    &newDispatch)) {
        Machine_Eal_Memory_copy(newDispatch->dispatch, oldDispatch->dispatch,
                                ((Machine_InterfaceType*)oldDispatch->dispatch->type)->size, false);
        Machine_Gc_lock(newDispatch->dispatch->type);
      }
    }
  }

  // Initialize interface dispatches.
  for (size_t i = 0, n = self->interfaces.implementations2.size; i < n; ++i) {
    Machine_InterfaceImplementation* implementation
        = Machine_Eal_InlineArray_getAt(&(self->interfaces.implementations2), i);
    Machine_InterfaceDispatchNode* dispatch = NULL;
    getOrCreateImplementation(self, implementation->interfaceType, true, &dispatch);
    dispatch->dispatch->type = (Machine_Type*)implementation->interfaceType;
    implementation->constructInterface(dispatch->dispatch);
  }

  _TypeFlag_set((Machine_Type*)self, Machine_TypeFlags_Initialized);
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
        = Machine_Eal_InlineArray_getAt(&(self->interfaces.dispatches2), i);
    if ((Machine_InterfaceType*)dispatchNode->dispatch->type == interfaceType) {
      return dispatchNode->dispatch;
    }
  }
  return NULL;
}
