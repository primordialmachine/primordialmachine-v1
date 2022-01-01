/// @file Input/Signals.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_INPUT_PRIVATE (1)
#include "Input/Signals.h"

/// @internal
/// @a true if the uninitialize callback was registered and was not run and unregistered yet.
/// @a false otherwise.
static bool g_registered = true;

#define DefineSignal(NAME, STRING) static Machine_String* _##NAME = NULL;
#include "Input/Signals.i"
#undef DefineSignal

static void uninitializeCallback() {
#define DefineSignal(NAME, STRING)                                                                 \
  if (_##NAME) {                                                                                   \
    Machine_Gc_unlock(_##NAME);                                                                    \
    _##NAME = NULL;                                                                                \
  }
#include "Input/Signals.i"
#undef DefineSignal
  g_registered = false;
}

static void ensureInitialized() {
  if (!g_registered) {
    if (!Machine_registerStaticVariables(&uninitializeCallback)) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    g_registered = true;
  }
#define DefineSignal(NAME, STRING)                                                                 \
  if (!_##NAME) {                                                                                  \
    _##NAME = Machine_String_create(STRING, c_strzt_length(STRING));                               \
  }
#include "Input/Signals.i"
#undef DefineSignal
}

#define DefineSignal(NAME, STRING)                                                                 \
  Machine_String* Machine_Input_SignalName_##NAME() {                                              \
    if (!_##NAME) {                                                                                \
      ensureInitialized();                                                                         \
    }                                                                                              \
    return _##NAME;                                                                                \
  }
#include "Input/Signals.i"
#undef DefineSignal
