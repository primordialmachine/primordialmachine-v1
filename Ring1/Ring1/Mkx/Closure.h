// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Closure.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_CLOSURE_H_INCLUDED)
#define MKX_CLOSURE_H_INCLUDED


#include "Ring1/Annotations/_Include.h"
#include "Ring1/Module.h"


Ring1_Module_Declare(Ring1, Closure)



/// @brief The type of a closure.
typedef struct Mkx_Closure Mkx_Closure;




/// @brief The type of a context of a closure.
typedef void Mkx_Closure_Context;

/// @brief Unconditionally cast a void pointer into a Mkx_Closure_Context pointer.
/// @param pointer The void pointer.
/// @return @a pointer cast into a Mkx_Closure_Context pointer.
static inline Mkx_Closure_Context*
MKX_CLOSURE_CONTEXT
  (
    void* pointer
  )
{ return (Mkx_Closure_Context*)pointer; }

/// @brief The type of a argument of a closure.
typedef void Mkx_Closure_Argument;

/// @brief Unconditionally cast a void pointer into a Mkx_Closure_Argument pointer.
/// @param pointer The void pointer.
/// @return @a pointer cast into a Mkx_Closure_Argument pointer.
static inline Mkx_Closure_Argument*
MKX_CLOSURE_ARGUMENT
  (
    void* pointer
  )
{ return (Mkx_Closure_Argument*)pointer; }




/// @brief Type of a function invoked when the closure is invoked.
/// @param context The context passed to the invocation.
/// @param argument The arguments passed to the invocation.
typedef int Mkx_Closure_Callback(Mkx_Closure_Context* context, Mkx_Closure_Argument *arguments);

/// @brief Unconditionally cast a void pointer into a Mkx_Closure_Callback pointer.
/// @param pointer The void pointer.
/// @return @a pointer cast into a Mkx_Closure_Callback pointer.
static inline Mkx_Closure_Callback *
MKX_CLOSURE_CALLBACK
  (
    void* pointer
  )
{ return (Mkx_Closure_Callback*)pointer; }




/// @brief Type of a function invoked before the closure is destroyed.
/// @param context The context of the closure.
/// @return @a 0 on success, a non-zero value on failure.
typedef int (Mkx_Closure_Notify)(Mkx_Closure_Context* context);

/// @brief Unconditionally cast a void pointer into a Mkx_Closure_Notify pointer.
/// @param pointer The void pointer.
/// @return @a pointer cast into a Mkx_Closure_Notify pointer.
static inline Mkx_Closure_Notify*
MKX_CLOSURE_NOTIFY
  (
    void* pointer
  )
{
  return (Mkx_Closure_Notify*)pointer;
}



/// @brief Create a closure.
/// @param result A pointer to a <code>Mkx_Closure *</code> variable.
/// @param context The context of the closure or a null pointer.
/// @param callback The callback function of the closure.
/// @param notify The notify function of the closure or a null pointer.
/// @post The reference count of the closure is @a 1.
Ring1_CheckReturn() int
Mkx_Closure_create
  (
    Mkx_Closure **result,
    Mkx_Closure_Context* context,
    Mkx_Closure_Callback *callback,
    Mkx_Closure_Notify *notify
  );

/// @brief Invoke a closure.
/// @param closure The closure.
/// @param argument The argument of the invocation.
/// @return @a 0 on success, a non-zero value on failure.
/// @error Ring1_Status_InvalidArgument @a closure is null.
/// @error The error returned by the closure callback.
Ring1_CheckReturn() int
Mkx_Closure_invoke
  (
    Mkx_Closure *closure,
    Mkx_Closure_Argument *argument
  );

/// @brief Increment the reference count of a closure by @a 1.
/// @param closure A pointer to the closure.
void
Mkx_Closure_reference
  (
    Mkx_Closure* self
  );

/// @brief Decrement the reference count of a closure by @a 1.
/// @param closure A pointer to the closure.
void
Mkx_Closure_unreference
  (
    Mkx_Closure *self
  );




#endif // MKX_CLOSURE_H_INCLUDED
