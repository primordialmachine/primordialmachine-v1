/// @file Ring3/Input/Signals.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_SIGNALS_H_INCLUDED)
#define RING3_INPUT_SIGNALS_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include ``Ring3/Input/Signals.h` directly, include `Ring3/Input/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

#define DefineSignal(Name, String) \
  Ring1_CheckReturn() Ring2_String* \
  Machine_Input_SignalName_##Name \
    ( \
    );
#include "Ring3/Input/Signals.i"
#undef DefineSignal

#endif // RING3_INPUT_SIGNALS_H_INCLUDED
