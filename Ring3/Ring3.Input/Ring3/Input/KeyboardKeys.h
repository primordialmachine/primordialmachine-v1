/// @file Ring3/Input/KeyboardKeys.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_KEYBOARDKEYS_H_INCLUDED)
#define RING3_INPUT_KEYBOARDKEYS_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include `Ring3/Input/KeyboardKeys.h` directly, include `Ring3/Input/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Machine_KeyboardKeys)

enum Machine_KeyboardKeys {

#define DefineKeyboardKey(NAME, STRING) Machine_KeyboardKeys_##NAME,

#include "Ring3/Input/KeyboardKeys.i"

#undef DefineKeyboardKey

};

Ring1_CheckReturn() Ring2_String*
Machine_KeyboardKeys_toString
  (
    Machine_KeyboardKeys self
  );

#endif // RING3_INPUT_KEYBOARDKEYS_H_INCLUDED
