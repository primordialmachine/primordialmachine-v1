/// @file Ring2/StaticVariables.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING2_STATICVARIABLES_H_INCLUDED)
#define RING2_STATICVARIABLES_H_INCLUDED


#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/StaticVariables.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"
#include "Ring1/Module.h"


Ring1_Module_Declare(Ring2, StaticVariablesModule)

typedef void(Ring2_UninitializeStaticVariablesCallback)();

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
/// Lazy initialize static variable of type Ring2_String.
/// <code>
/// static Ring2_String* g_string = NULL;
///
/// static void uninitializeStaticVariablesCallback() {
///   if (g_string) {
///     Ring2_Gc_unlock(g_string);
///     g_string = NULL;
///   }
/// }
///
/// Ring2_String *getString() {
///   if (!g_string) {
///     g_string = Ring2_String_create(...);
///     Ring2_Gc_lock(g_string);
///     if (Ring2_registerStaticVariables(&uninitializeStaticVariablesCallback)) {
///       Machine_Gc_unlock(g_string);
///       g_string = NULL;
///     }
///
///   }
///   return g_string;
/// }
/// </code>
Ring1_CheckReturn() Ring1_Result
Ring2_registerStaticVariables
  (
    Ring2_UninitializeStaticVariablesCallback* callback
  );

void
Ring2_notifyStaticVariablesUninitialize
  (
  );


#endif // RING2_STATICVARIABLESMODULE_H_INCLUDED
