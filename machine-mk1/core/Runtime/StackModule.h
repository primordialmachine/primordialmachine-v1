/// @file Runtime/StackModule.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_STACKMODULE_H_INCLUDED)
#define MACHINE_RUNTIME_STACKMODULE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/StackModule.h` directly, include `_Runtime.h` instead.")
#endif
#include "Ring2/_Include.h"

Ring1_Result Machine_initializeStackModule();

void Machine_uninitializeStackModule();

/// @brief Load a <code>Boolean</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_AllocationFailed An allocation failed.
void Machine_Stack_loadBoolean(Ring2_Boolean value);

/// @brief Load an <code>Integer</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_AllocationFailed An allocation failed.
void Machine_Stack_loadInteger(Ring2_Integer value);

/// @brief Load a <code>ForeignProcedure</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_AllocationFailed An allocation failed.
void Machine_Stack_loadForeignProcedure(Ring2_ForeignProcedure* value);

/// @brief Load an <code>Object</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_AllocationFailed An allocation failed.
void Machine_Stack_loadObject(Machine_Object* value);

/// @brief Load a <code>Real</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_AllocationFailed An allocation failed.
/// @error Machine_Status_CapacityExhausted The stack can not grow any further.
void Machine_Stack_loadReal(Ring2_Real32 value);

/// @brief Load a <code>String</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_AllocationFailed An allocation failed.
/// @error Machine_Status_CapacityExhausted The stack can not grow any further.
void Machine_Stack_loadString(Ring2_String* value);

/// @brief Load a <code>Void</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_AllocationFailed An allocation failed.
/// @error Machine_Status_CapacityExhausted The stack can not grow any further.
void Machine_Stack_loadVoid(Ring2_Void value);

/// @brief Load a value on the stack.
/// @param value The value.
/// @error Machine_Status_AllocationFailed An allocation failed.
/// @error Machine_Status_CapacityExhausted The stack can not grow any further.
void Machine_Stack_load(Ring2_Value value);

/// @brief Peek at the value at the specified stack index.
/// @param index The stack index.
/// Must be within the bounds of [0,n-1] where n is the size of the stack.
/// @return The value.
/// @error Machine_Status_IndexOutOfbounds The index is out of bounds.
Ring2_Value Machine_Stack_peek(size_t index);

/// @brief Pop a value from the stack.
/// @param stack a pointer to the stack
/// @error Machine_Status_Empty The stack is empty.
void Machine_Stack_pop();

/// @brief Get the size of the stack.
/// @return The size.
size_t Machine_Stack_getSize();

#endif // MACHINE_RUNTIME_JUMPTARGETMODULE_H_INCLUDED
