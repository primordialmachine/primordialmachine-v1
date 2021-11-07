/// @file Runtime/StackModule.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_STACKMODULE_H_INCLUDED)
#define MACHINE_RUNTIME_STACKMODULE_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "_Eal.h"
#include "Runtime/Status.h"
#include "Runtime/Value.h"



Machine_StatusValue Machine_initializeStackModule();

void Machine_uninitializeStackModule();

/// @brief Load a <code>Boolean</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadBoolean(Machine_Boolean value);

/// @brief Load an <code>Integer</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadInteger(Machine_Integer value);

/// @brief Load a <code>ForeignProcedure</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadForeignProcedure(Machine_ForeignProcedure* value);

/// @brief Load an <code>Object</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadObject(Machine_Object* value);

/// @brief Load a <code>Real</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadReal(Machine_Real value);

/// @brief Load a <code>String</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadString(Machine_String* value);

/// @brief Load a <code>Void</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadVoid(Machine_Void value);



#endif // MACHINE_RUNTIME_JUMPTARGETMODULE_H_INCLUDED
