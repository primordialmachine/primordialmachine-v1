/// @file Input/KeyboardKeys.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_INPUT_KEYBOARDKEYS_H_INCLUDED)
#define MACHINE_INPUT_KEYBOARDKEYS_H_INCLUDED

#if !defined(MACHINE_INPUT_PRIVATE)
#error("Do not include this file directly, include `_Input.h` instead.")
#endif
#include "_Runtime.h"

typedef enum Machine_KeyboardKeys {

#define DefineKeyboardKey(NAME, STRING) Machine_KeyboardKeys_##NAME,

#include "Input/KeyboardKeys.i"

#undef DefineKeyboardKey

} Machine_KeyboardKeys;

Machine_String* Machine_KeyboardKeys_toString(Machine_KeyboardKeys self);

#endif // MACHINE_INPUT_KEYBOARDKEYS_H_INCLUDED
