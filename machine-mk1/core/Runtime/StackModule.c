/// @file Runtime/StackModule.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/StackModule.h"

#include "_Eal.h"
#include "Ring1/Status.h"
#include "Runtime/JumpTargetModule.h"

typedef struct Stack {
  Machine_Value* elements;
  size_t size, capacity;
} Stack;

static Machine_StatusValue Stack_initialize(Stack* self) {
  self->elements = NULL;
  if (Ring1_Memory_allocateArray(&self->elements, 8, sizeof(Machine_Value))) {
    Ring1_Status_set(Ring1_Status_Success);
    return Machine_Status_AllocationFailed;
  }
  for (size_t i = 0; i < 8; ++i) {
    Machine_Value_setVoid(self->elements + i, Machine_Void_Void);
  }
  self->size = 0;
  self->capacity = 8;
  return Machine_Status_Success;
}

static void Stack_uninitialize(Stack* self) {
  if (self->elements) {
    Ring1_Memory_deallocate(self->elements);
    self->elements = NULL;
  }
}

static Machine_StatusValue Stack_create(Stack** stack) {
  Stack* stack0 = NULL;
  if (Ring1_Memory_allocate(&stack0, sizeof(Stack))) {
    Ring1_Status_set(Ring1_Status_Success);
    return Machine_Status_AllocationFailed;
  }
  Machine_StatusValue status = Stack_initialize(stack0);
  if (status) {
    Ring1_Memory_deallocate(stack0);
    return status;
  }
  *stack = stack0;
  return Machine_Status_Success;
}

static void Stack_destroy(Stack* stack) {
  Stack_uninitialize(stack);
  Ring1_Memory_deallocate(stack);
}

static void Stack_grow(Stack* self, size_t additionalCapacity) {
  size_t newCapacity = 0;
  if (Ring1_Memory_recomputeSize_sz(0, SIZE_MAX / sizeof(Machine_Value), self->capacity,
                                    additionalCapacity, &newCapacity, true)) {
    Machine_setStatus(Machine_Status_CapacityExhausted);
    Machine_jump();
  }
  Machine_Value* newElements = NULL;
  if (Ring1_Memory_reallocateArray(&newElements, self->elements, newCapacity,
                                   sizeof(Machine_Value))) {
    Ring1_Status_set(Ring1_Status_Success);
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->elements = newElements;
  self->capacity = newCapacity;
}

static void Stack_ensureFreeCapacity(Stack* self, size_t requiredFreeCapacity) {
  size_t availableFreeCapacity = self->capacity - self->size;
  if (availableFreeCapacity < requiredFreeCapacity) {
    size_t requiredAdditionalCapacity = requiredFreeCapacity - availableFreeCapacity;
    Stack_grow(self, requiredAdditionalCapacity);
  }
}

static Stack* g_stack = NULL;
static Ring1_Memory_ModuleHandle g_memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;

Machine_StatusValue Machine_initializeStackModule() {
  Machine_StatusValue status;
  g_memoryModuleHandle = Ring1_Memory_ModuleHandle_acquire();
  if (!g_memoryModuleHandle) {
    return Machine_Status_EnvironmentFailed;
  }
  status = Stack_create(&g_stack);
  if (status) {
    Ring1_Memory_ModuleHandle_relinquish(g_memoryModuleHandle);
    g_memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;
    return status;
  }
  return Machine_Status_Success;
}

void Machine_uninitializeStackModule() {
  Stack_destroy(g_stack);
  g_stack = NULL;
  Ring1_Memory_ModuleHandle_relinquish(g_memoryModuleHandle);
  g_memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;
}

void Machine_Stack_loadBoolean(Machine_Boolean value) {
  Machine_Value temporary;
  Machine_Value_setBoolean(&temporary, value);
  Machine_Stack_load(temporary);
}

void Machine_Stack_loadInteger(Machine_Integer value) {
  Machine_Value temporary;
  Machine_Value_setInteger(&temporary, value);
  Machine_Stack_load(temporary);
}

void Machine_Stack_loadForeignProcedure(Machine_ForeignProcedure* value) {
  Machine_Value temporary;
  Machine_Value_setForeignProcedure(&temporary, value);
  Machine_Stack_load(temporary);
}

void Machine_Stack_loadObject(Machine_Object* value) {
  Machine_Value temporary;
  Machine_Value_setObject(&temporary, value);
  Machine_Stack_load(temporary);
}

void Machine_Stack_loadReal(Machine_Real value) {
  Machine_Value temporary;
  Machine_Value_setReal(&temporary, value);
  Machine_Stack_load(temporary);
}

void Machine_Stack_loadString(Machine_String* value) {
  Machine_Value temporary;
  Machine_Value_setString(&temporary, value);
  Machine_Stack_load(temporary);
}

void Machine_Stack_loadVoid(Machine_Void value) {
  Machine_Value temporary;
  Machine_Value_setVoid(&temporary, value);
  Machine_Stack_load(temporary);
}

void Machine_Stack_load(Machine_Value value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  *(g_stack->elements + g_stack->size) = value;
  g_stack->size++;
}

Machine_Value Machine_Stack_peek(size_t index) {
  if (index >= g_stack->size) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  return *(g_stack->elements + g_stack->size - 1 - index);
}

void Machine_Stack_pop() {
  if (g_stack->size == 0) {
    Machine_setStatus(Machine_Status_Empty);
    Machine_jump();
  }
  g_stack->size -= 1;
}

size_t Machine_Stack_getSize() {
  return g_stack->size;
}
