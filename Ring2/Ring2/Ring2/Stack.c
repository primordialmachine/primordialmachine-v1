// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Stack.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Stack.h"
#undef RING2_PRIVATE


#include "Ring1/Log.h"
#include "Ring1/All/_Include.h"
#define RING2_PRIVATE (1)
#include "Ring2/JumpTarget.h"
#include "Ring2/Types/Value.h"
#undef RING2_PRIVATE
#include <assert.h>


typedef struct Mkx_Interpreter_Stack Mkx_Interpreter_Stack;

struct Mkx_Interpreter_Stack {
  Ring2_Value* values;
  int64_t size;
  int64_t capacity;
  Ring1_Memory_ModuleHandle memoryModuleHandle;
};

#define MIN_CAPACITY ((int64_t)1)
static_assert(MIN_CAPACITY <= INT64_MAX, "MIN_CAPACITY must be smaller than or equal to INT64_MAX");
static_assert(0 <= MIN_CAPACITY, "MIN_CAPACITY must be greater than or equal to 0");

#define MAX_CAPACITY (INT64_MAX / ((int64_t)sizeof(Ring2_Value)))
static_assert(MAX_CAPACITY <= INT64_MAX, "MAX_CAPACITY must be smaller than or equal to INT64_MAX");
static_assert(0 <= MAX_CAPACITY, "MAX_CAPACITY must be greater than or equal to 0");

static_assert(MIN_CAPACITY <= MAX_CAPACITY, "MIN_CAPACITY must be smaller than or equal to MAX_CAPACITY");

static Mkx_Interpreter_Stack* g_stack = NULL;

// Grow stack by at least the specified amount.
// @param required The required additional capacity.
// Must be non-negative.
// @throw @a required is negative
// @throw New capacity exceeds maximal capacity.
static void
grow
  (
    Ring2_Context* context,
    Ring2_Integer required
  );

static void
ensureFreeCapacity
  (
    Ring2_Context* context,
    Ring2_Integer required
  );

static Mkx_Interpreter_Stack*
Mkx_Interpreter_Stack_create
  (
  );

static void
Mkx_Interpreter_Stack_destroy
  (
    Mkx_Interpreter_Stack* stack
  );

static void
grow
  (
    Ring2_Context* context,
    Ring2_Integer required
  )
{
  assert(NULL != context);
  assert(NULL != g_stack);

  Ring2_Integer oldCapacity = g_stack->capacity,
                newCapacity = 0;
  if (Ring1_Memory_recomputeSize_s64(MIN_CAPACITY, MAX_CAPACITY, oldCapacity, required, &newCapacity, true)) {
    Ring1_Log_error("unable to increase capacity");
    Ring2_jump();
  }
  // Perform reallocation.
  Ring2_Value *oldValues = g_stack->values;
  Ring2_Value *newValues;
  if (Ring1_Memory_allocate(&newValues, sizeof(Ring2_Value) * (size_t)newCapacity)) {
    Ring2_jump();
  }
  Ring1_Memory_copyFast(newValues, oldValues, sizeof(Ring2_Value) * (size_t)oldCapacity);
  Ring1_Memory_deallocate(oldValues);
  g_stack->capacity = newCapacity;
  g_stack->values = newValues;
  for (Ring2_Integer i = oldCapacity, n = newCapacity; i < n; ++i) {
    Ring2_Value_setVoid(g_stack->values + i, Ring2_Void_Void);
  }
}

static void
ensureFreeCapacity
  (
    Ring2_Context *context,
    Ring2_Integer required
  )
{
  if (!required) {
    return;
  }
  if (required < 0) {
    Ring1_Log_error("invalid argument");
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    Ring2_jump();
  }
  int64_t actual = g_stack->capacity - g_stack->size;
  if (actual > required) return;
  grow(context, required - actual);
}

Mkx_Interpreter_Stack *
Mkx_Interpreter_Stack_create
  (
  )
{
  Ring1_Memory_ModuleHandle handle = Ring1_Memory_ModuleHandle_acquire();
  if (!handle) {
    return NULL;
  }
  Mkx_Interpreter_Stack* stack;
  if (Ring1_Memory_allocate(&stack, sizeof(Mkx_Interpreter_Stack))) {
    Ring1_Memory_ModuleHandle_relinquish(handle);
    return NULL;
  }
  stack->size = 0;
  stack->capacity = 8;
  if (Ring1_Memory_allocate(&stack->values, (size_t)stack->capacity * sizeof(Ring2_Value))) {
    Ring1_Memory_deallocate(stack);
    stack = NULL;
    Ring1_Memory_ModuleHandle_relinquish(handle);
    return NULL;
  }
  for (size_t i = 0, n = 8; i < n; ++i) {
    Ring2_Value_setVoid(stack->values + i, Ring2_Void_Void); 
  }
  stack->memoryModuleHandle = handle;
  return stack;
}

void
Mkx_Interpreter_Stack_destroy
  (
    Mkx_Interpreter_Stack *stack
  )
{
  Ring1_Memory_ModuleHandle handle = stack->memoryModuleHandle;
  Ring1_Memory_deallocate(stack->values);
  stack->values = NULL;
  Ring1_Memory_deallocate(stack);
  Ring1_Memory_ModuleHandle_relinquish(handle);
}

static Ring2_Gc_PreMarkCallbackId g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;

Ring1_CheckReturn() Ring1_Result
Mkx_Interpreter_Stack_startup
  (
  )
{
  g_stack = Mkx_Interpreter_Stack_create();
  if (!g_stack) {
    Ring1_Result_Failure;
  }
  g_preMarkCallbackId = Ring2_Gc_addPreMarkCallback(Ring2_Gc_get(), NULL,
                                                    (Ring2_Gc_PreMarkCallback *)&Mkx_Interpreter_Stack_preMark);
  if (!g_preMarkCallbackId) {
    Mkx_Interpreter_Stack_destroy(g_stack);
    g_stack = NULL;
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

void
Mkx_Interpreter_Stack_shutdown
  (
  )
{
  Ring2_Gc_removePreMarkCallback(Ring2_Gc_get(), g_preMarkCallbackId);
  g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;

  Mkx_Interpreter_Stack_destroy(g_stack);
  g_stack = NULL;
}

Ring1_Module_Define(Ring2, StackModule, Mkx_Interpreter_Stack_startup, Mkx_Interpreter_Stack_shutdown)

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

void
Mkx_Interpreter_Stack_pushArray
  (
    Ring2_Context* context,
    Ring2_Array* x
  )
{
  ensureFreeCapacity(context, 1);
  Ring2_Value_setArray(g_stack->values + g_stack->size, x);
  g_stack->size++;
}

#endif

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

void
Mkx_Interpreter_Stack_pushBoolean
  (
    Ring2_Context* context,
    Ring2_Boolean x
  )
{
  ensureFreeCapacity(context, 1);
  Ring2_Value_setBoolean(g_stack->values + g_stack->size, x);
  g_stack->size++;
}

#endif

#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

void
Mkx_Interpreter_Stack_pushForeignProcedure
  (
    Ring2_Context* context,
    Ring2_ForeignProcedure* x
  )
{
  ensureFreeCapacity(context, 1);
  Ring2_Value_setForeignProcedure(g_stack->values + g_stack->size, x);
  g_stack->size++;
}

#endif

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

void
Mkx_Interpreter_Stack_pushInteger
  (
    Ring2_Context* context,
    Ring2_Integer x
  )
{
  ensureFreeCapacity(context, 1);
  Ring2_Value_setInteger(g_stack->values + g_stack->size, x);
  g_stack->size++;
}

#endif

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

void
Mkx_Interpreter_Stack_pushObject
  (
    Ring2_Context *context,
    Machine_Object *x
  )
{
  ensureFreeCapacity(context, 1);
  Ring2_Value_setObject(g_stack->values + g_stack->size, x);
  g_stack->size++;
}

#endif

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

void
Mkx_Interpreter_Stack_pushReal
  (
    Ring2_Context* context,
    Ring2_Real64 x
  )
{
  ensureFreeCapacity(context, 1);
  Ring2_Value_setReal64(g_stack->values + g_stack->size, x);
  g_stack->size++;
}

#endif

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

void
Mkx_Interpreter_Stack_pushString
  (
    Ring2_Context* context,
    Ring2_String*x
  )
{
  ensureFreeCapacity(context, 1);
  Ring2_Value_setString(g_stack->values + g_stack->size, x);
  g_stack->size++;
}

#endif

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

void
Mkx_Interpreter_Stack_pushVoid
  (
    Ring2_Context* context,
    Ring2_Void x
  )
{
  ensureFreeCapacity(context, 1);
  Ring2_Value_setVoid(g_stack->values + g_stack->size, x);
  g_stack->size++;
}

#endif

void
Mkx_Interpreter_Stack_push
  (
    Ring2_Context* context,
    Ring2_Value const* value
  )
{
  ensureFreeCapacity(context, 1);
  Ring2_Value_set(g_stack->values + g_stack->size, value);
  g_stack->size++;
}

/*PREMARK*/ void
Mkx_Interpreter_Stack_preMark
  (
    Ring2_Gc* gc,
    void *context
  )
{
  for (int64_t i = 0, n = g_stack->size; i < n; ++i)
  {
    Ring2_Value_visit(gc, g_stack->values + i);
  }
}

Ring1_CheckReturn() Ring2_Integer
Mkx_Interpreter_Stack_getSize
  (
    Ring2_Context* context
  )
{ return g_stack->size; }

void
Mkx_Interpreter_Stack_clear
  (
    Ring2_Context* context
  )
{ g_stack->size = 0; }

Ring2_Value *
Mkx_Interpreter_Stack_getAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  if (stackIndex >= g_stack->size) {
    return NULL;
  }
  return g_stack->values + g_stack->size - 1 - stackIndex;
}

Ring2_Integer
Mkx_Interpreter_Stack_pop
  (
    Ring2_Context* context,
    Ring2_Integer count
  )
{
  int64_t i = count < g_stack->size ? count : g_stack->size;
  g_stack->size -= i;
  return i;
}

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

Ring2_Array*
Mkx_Interpreter_Stack_getArrayAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  if (Ring1_Unlikely(!Ring2_Value_isArray(value))) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getArray(value);
}

Ring2_Boolean
Mkx_Interpreter_Stack_isArrayAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value *value = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  return Ring2_Value_isArray(value);
}

#endif

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

Ring2_Boolean
Mkx_Interpreter_Stack_getBooleanAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  if (Ring1_Unlikely(!Ring2_Value_isBoolean(value))) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getBoolean(value);
}

Ring2_Boolean
Mkx_Interpreter_Stack_isBooleanAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value *value = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  return Ring2_Value_isBoolean(value);
}

#endif

#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

Ring2_ForeignProcedure*
Mkx_Interpreter_Stack_getForeignProcedureAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value *value  = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  if (Ring1_Unlikely(!Ring2_Value_isForeignProcedure(value))) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getForeignProcedure(value);
}

Ring2_Boolean
Mkx_Interpreter_Stack_isForeignProcedureAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  return Ring2_Value_isForeignProcedure(value);
}

#endif

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

Ring2_Integer
Mkx_Interpreter_Stack_getIntegerAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value *value  = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  if (Ring1_Unlikely(!Ring2_Value_isInteger(value))) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getInteger(value);
}

Ring2_Boolean
Mkx_Interpreter_Stack_isIntegerAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  return Ring2_Value_isInteger(value);
}

#endif

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

Ring2_Real64
Mkx_Interpreter_Stack_getRealAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value *value  = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  if (Ring1_Unlikely(!Ring2_Value_isReal64(value))) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getReal64(value);
}

Ring2_Boolean
Mkx_Interpreter_Stack_isRealAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value *value = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  return Ring2_Value_isReal64(value);
}

#endif

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

Machine_Object *
Mkx_Interpreter_Stack_getObjectAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value *value  = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  if (Ring1_Unlikely(!Ring2_Value_isObject(value))) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getObject(value);
}

Ring2_Boolean
Mkx_Interpreter_Stack_isObjectAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  return Ring2_Value_isObject(value);
}

#endif

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

Ring2_String*
Mkx_Interpreter_Stack_getStringAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value *value  = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) { 
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  if (Ring1_Unlikely(!Ring2_Value_isString(value))) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getString(value);
}

Ring2_Boolean
Mkx_Interpreter_Stack_isStringAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  return Ring2_Value_isString(value);
}

#endif

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

Ring2_Void
Mkx_Interpreter_Stack_getVoidAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value *value  = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    Ring2_jump();
  }
  if (Ring1_Unlikely(!Ring2_Value_isVoid(value))) {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  }
  return Ring2_Value_getVoid(value);
}

Ring2_Boolean
Mkx_Interpreter_Stack_isVoidAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  )
{
  Ring2_Value* value = Mkx_Interpreter_Stack_getAt(context, stackIndex);
  if (Ring1_Unlikely(!value)) {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  return Ring2_Value_isVoid(value);
}

#endif
