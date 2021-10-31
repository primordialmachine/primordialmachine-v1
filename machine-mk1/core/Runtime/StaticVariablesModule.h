/// @file Runtime/StaticVariablesModule.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_STATICVARIABLESMODULE_H_INCLUDED)
#define MACHINE_RUNTIME_STATICVARIABLESMODULE_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "C.h"
#include "Runtime/Status.h"



Machine_StatusValue Machine_initializeStaticVariablesModule();

void Machine_uninitializeStaticVariablesModule();

typedef void (Machine_UninitializeStaticVariablesCallback)();

/// @brief Register an uninitialize static fields callback.
/// @param callback The callback.
/// @return @a true if the callback was registered, @a false otherwise.
/// 
/// @remarks
/// This callback is invoked once when the GC performs cycles before machine shutdown.
/// That is these callbacks are 
/// - The GC performs cycles until no more objects are destroyed.
/// - The uninitialize static variables callback is invoked.
/// - The GC performs cycles until no more objects are destroyed.
/// 
///
/// @example
/// Use this to create and destroy string constants.
/// Do not use this for other variables
/// Lazy initialize static variable of type Machine_String.
/// <code>
/// static Machine_String* g_string = NULL;
/// 
/// static void uninitializeStaticVariablesCallback() {
///   if (g_string) {
///     Machine_unlock(g_string);
///     g_String = NULL;
///   }
/// }
/// 
/// Machine_String *getString() {
///   if (!g_string) {
///     g_string = Machine_String_create(...);
///     Machine_lock(g_string);
///     if (!Machine_registerStaticVariables(&callback)) {
///       Machine_unlock(g_string);
///       g_string = NULL;
///     }
///   
///   }
///   return g_string;
/// }
/// </code>
bool Machine_registerStaticVariables(Machine_UninitializeStaticVariablesCallback* callback);

void Machine_notifyStaticVariablesUninitialize();


#endif // MACHINE_RUNTIME_STATICVARIABLESMODULE_H_INCLUDED
