/// @file Runtime/StackModule.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/StackModule.h"



#include "Runtime/JumpTargetModule.h"



typedef struct Stack {
  Machine_Value* elements;
  size_t size, capacity;
} Stack;

static Machine_StatusValue Stack_initialize(Stack* self) {
  self->elements = Machine_Eal_alloc_a(sizeof(Machine_Value), 8);
  if (!self->elements) {
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
    Machine_Eal_dealloc(self->elements);
    self->elements = NULL;
  }
}

static Machine_StatusValue Stack_create(Stack** stack) {
  Stack* stack0 = Machine_Eal_alloc(sizeof(Stack));
  if (!stack0) {
    return Machine_Status_AllocationFailed;
  }
  Machine_StatusValue status = Stack_initialize(stack0);
  if (status) {
    Machine_Eal_dealloc(stack0);
    return status;
  }
  *stack = stack0;
  return Machine_Status_Success;
}

static void Stack_destroy(Stack* stack) {
  Stack_uninitialize(stack);
  Machine_Eal_dealloc(stack);
}

static void Stack_ensureFreeCapacity(Stack* self, size_t requiredFreeCapacity) {
  size_t availableFreeCapacity = self->capacity - self->size;
  if (availableFreeCapacity < requiredFreeCapacity) {
    size_t requiredAdditionalCapacity = requiredFreeCapacity - availableFreeCapacity;
    size_t maximalCapacity = SIZE_MAX / sizeof(Machine_Value);
    size_t availableAdditionalCapacity = maximalCapacity - self->capacity;
    if (availableAdditionalCapacity < requiredAdditionalCapacity) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    // TODO: This ensures that we have enough free capacity in any case.
    // However, we should try to allocate more to avoid reallocating over and over.
    size_t newCapacity = self->capacity + requiredAdditionalCapacity;
    Machine_Value* newElements = c_realloc_a(self->elements, sizeof(Machine_Value), newCapacity);
    if (newElements) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->elements = newElements;
    self->capacity = newCapacity;
  }
}

static Stack* g_stack = NULL;

Machine_StatusValue Machine_initializeStackModule() {
  Machine_StatusValue status;
  status = Stack_create(&g_stack);
  if (status) {
    return status;
  }
  return Machine_Status_Success;
}

void Machine_uninitializeStackModule() {
  Stack_destroy(g_stack);
  g_stack = NULL;
}
void Machine_loadBoolean(Machine_Boolean value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setBoolean(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadInteger(Machine_Integer value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setInteger(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadForeignProcedure(Machine_ForeignProcedure* value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setForeignProcedure(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadObject(Machine_Object* value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setObject(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadReal(Machine_Real value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setReal(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadString(Machine_String* value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setString(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadVoid(Machine_Void value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setVoid(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}
