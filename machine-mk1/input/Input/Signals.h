/// @file Input/Signals.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_INPUT_SIGNALS_H_INCLUDED)
#define MACHINE_INPUT_SIGNALS_H_INCLUDED

#if !defined(MACHINE_INPUT_PRIVATE)
#error("Do not include this file directly, include `_Input.h` instead.")
#endif
#include "_Runtime.h"

#define DefineSignal(Name, String) Machine_String* Machine_Input_SignalName_##Name();
#include "Input/Signals.i"
#undef DefineSignal

#endif // MACHINE_INPUT_SIGNALS_H_INCLUDED
