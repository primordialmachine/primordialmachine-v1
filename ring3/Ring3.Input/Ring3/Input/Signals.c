/// @file Ring3/Input/Signals.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/Signals.h"

/// @internal
/// @a true if the uninitialize callback was registered and was not run and unregistered yet.
/// @a false otherwise.
static bool g_registered = true;

#define DefineSignal(NAME, STRING) static Ring2_String* _##NAME = NULL;
#include "Ring3/Input/Signals.i"
#undef DefineSignal

static void uninitializeCallback() {
#define DefineSignal(NAME, STRING)                                                                 \
  if (_##NAME) {                                                                                   \
    Ring2_Gc_unlock(_##NAME);                                                                    \
    _##NAME = NULL;                                                                                \
  }
#include "Ring3/Input/Signals.i"
#undef DefineSignal
  g_registered = false;
}

static void
ensureInitialized
  (
  )
{
  if (!g_registered) {
    if (Ring2_registerStaticVariables(&uninitializeCallback)) {
      Ring2_jump();
    }
    g_registered = true;
  }
#define DefineSignal(NAME, STRING)                                                                 \
  if (!_##NAME) {                                                                                  \
    _##NAME = Ring2_String_fromC(STRING);                                                          \
  }
#include "Ring3/Input/Signals.i"
#undef DefineSignal
}

#define DefineSignal(NAME, STRING)                                                                 \
  Ring1_CheckReturn() Ring2_String* \
  Machine_Input_SignalName_##NAME \
    ( \
    ) \
  { \
    if (!_##NAME) {                                                                                \
      ensureInitialized();                                                                         \
    }                                                                                              \
    return _##NAME;                                                                                \
  }
#include "Ring3/Input/Signals.i"
#undef DefineSignal
