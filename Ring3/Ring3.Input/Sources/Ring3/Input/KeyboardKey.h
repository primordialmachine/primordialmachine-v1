/// @file Ring3/Input/KeyboardKey.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_KEYBOARDKEY_H_INCLUDED)
#define RING3_INPUT_KEYBOARDKEY_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include `Ring3/Input/KeyboardKey.h` directly, include `Ring3/Input/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_KeyboardKey)

enum Ring3_KeyboardKey {

#define DefineKeyboardKey(NAME, STRING) Ring3_KeyboardKey_##NAME,

#include "Ring3/Input/KeyboardKey.i"

#undef DefineKeyboardKey

};

Ring1_CheckReturn() Ring2_String*
Ring3_KeyboardKey_toString
  (
    Ring3_KeyboardKey self
  );

#endif // RING3_INPUT_KEYBOARDKEY_H_INCLUDED
