// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Stack.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_STACK_H_INCLUDED)
#define RING2_LIBRARY_STACK_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Stack.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @brief A stack.
MACHINE_DECLARE_INTERFACETYPE(Ring2_Stack)

struct Ring2_Stack_Dispatch {
  Machine_InterfaceDispatch parent;

  Ring2_Value (*pop)(Ring2_Stack* self);
  void (*push)(Ring2_Stack* self, Ring2_Value value);
};

/// @brief Pop the value on top of this stack.
/// @param self This stack.
/// @return The value.
Ring2_Value
Ring2_Stack_pop
  (
    Ring2_Stack* self
  );

/// @brief Push a value on the top of this stack.
/// @param self A pointer to this stack.
/// @param value The value.
void
Ring2_Stack_push
  (
    Ring2_Stack* self,
    Ring2_Value value
  );


#endif // RING2_LIBRARY_STACK_H_INCLUDED
