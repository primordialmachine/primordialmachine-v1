// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Stack.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_STACK_H_INCLUDED)
#define RING2_STACK_H_INCLUDED

#include "Ring2/Configuration.h"
#include "Ring2/Types/Value.h"
#include "Ring2/Gc.h"

Ring1_CheckReturn() Ring1_Result
Mkx_Interpreter_Stack_startup
  (
  );

void
Mkx_Interpreter_Stack_shutdown
  (
  );

/*PREMARK*/ void
Mkx_Interpreter_Stack_preMark
  (
    Ring2_Gc* gc,
    void* context
  );

Ring2_Value*
Mkx_Interpreter_Stack_getAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

void
Mkx_Interpreter_Stack_pushArray
  (
    Ring2_Context* context,
    Ring2_Array* x
  );

Ring2_Array*
Mkx_Interpreter_Stack_getArrayAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

Ring2_Boolean
Mkx_Interpreter_Stack_isArrayAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

#endif

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

void
Mkx_Interpreter_Stack_pushBoolean
  (
    Ring2_Context* context,
    Ring2_Boolean x
  );

Ring2_Boolean
Mkx_Interpreter_Stack_getBooleanAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

Ring2_Boolean
Mkx_Interpreter_Stack_isBooleanAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

#endif

#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

void
Mkx_Interpreter_Stack_pushForeignProcedure
  (
    Ring2_Context* context,
    Ring2_ForeignProcedure* x
  );

Ring2_ForeignProcedure*
Mkx_Interpreter_Stack_getForeignProcedureAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

Ring2_Boolean
Mkx_Interpreter_Stack_isForeignProcedureAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

#endif

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

void
Mkx_Interpreter_Stack_pushInteger
  (
    Ring2_Context* context,
    Ring2_Integer x
  );

Ring2_Integer
Mkx_Interpreter_Stack_getIntegerAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

Ring2_Boolean
Mkx_Interpreter_Stack_isIntegerAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

#endif

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

void
Mkx_Interpreter_Stack_pushObject
  (
    Ring2_Context *context,
    Machine_Object *x
  );

Machine_Object *
Mkx_Interpreter_Stack_getObjectAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

Ring2_Boolean
Mkx_Interpreter_Stack_isObjectAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

#endif

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

void
Mkx_Interpreter_Stack_pushReal
  (
    Ring2_Context* context,
    Ring2_Real64 x
  );

Ring2_Real64
Mkx_Interpreter_Stack_getRealAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

Ring2_Boolean
Mkx_Interpreter_Stack_isRealAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

#endif

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

void
Mkx_Interpreter_Stack_pushString
  (
    Ring2_Context* context,
    Ring2_String* x
  );

Ring2_String*
Mkx_Interpreter_Stack_getStringAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

Ring2_Boolean
Mkx_Interpreter_Stack_isStringAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

#endif

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

void
Mkx_Interpreter_Stack_pushVoid
  (
    Ring2_Context* context,
    Ring2_Void x
  );

Ring2_Void
Mkx_Interpreter_Stack_getVoidAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

Ring2_Boolean
Mkx_Interpreter_Stack_isVoidAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

#endif

/// @brief Push a value on the stack.
/// @param context The context.
/// @param stack A pointer to the stack.
/// @param value A pointer to the value.
void
Mkx_Interpreter_Stack_push
  (
    Ring2_Context* context,
    Ring2_Value const* value
  );

/*PREMARK*/ void
Mkx_Interpreter_Stack_preMark
  (
    Ring2_Gc* gc,
    void* context
  );

Ring1_CheckReturn() Ring2_Integer
Mkx_Interpreter_Stack_getSize
  (
    Ring2_Context* context
  );

void
Mkx_Interpreter_Stack_clear
  (
    Ring2_Context* context
  );

/// @brief Get the value at the specified stack index.
/// @param stack A poiner to the stack.
/// @param stackIndex The stack index.
/// @return A pointer to the value on success, a null pointer on failure.
/// This function fails iff @a stack is a null pointer or @a stackIndex is out of bounds.
Ring2_Value*
Mkx_Interpreter_Stack_getAt
  (
    Ring2_Context* context,
    Ring2_Integer stackIndex
  );

/// @brief Pop @a count items from the stack.
/// @param count The maximum number of items to pop.
/// @return The actual number of items which were popped.
/// @remark This function pops @a count items if there are at least @a count items on the stack.
/// Otherwise it pops all items from the stack.
Ring2_Integer
Mkx_Interpreter_Stack_pop
  (
    Ring2_Context* context,
    Ring2_Integer count
  );

#endif // RING2_STACK_H_INCLUDED
