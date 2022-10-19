// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/Stack.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_COLLECTIONS_STACK_H_INCLUDED)
#define RING2_LIBRARY_COLLECTIONS_STACK_H_INCLUDED


#if !defined(RING2_LIBRARY_COLLECTIONS_PRIVATE) || 1 != RING2_LIBRARY_COLLECTIONS_PRIVATE
#error("Do not include `Ring2/Library/Collections/Stack.h` directly. Include `Ring2/Library/Collections/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @extends Ring2.Collections.Stack
/// @brief A stack.
MACHINE_DECLARE_INTERFACETYPE(Ring2_Collections_Stack)

struct Ring2_Collections_Stack_Dispatch {
  Machine_InterfaceDispatch parent;

  Ring2_Value (*pop)(Ring2_Collections_Stack* self);
  void (*push)(Ring2_Collections_Stack* self, Ring2_Value value);
};

/// @brief Pop the value on top of this stack.
/// @param self This stack.
/// @return The value.
Ring2_Value
Ring2_Collections_Stack_pop
  (
    Ring2_Collections_Stack* self
  );

/// @brief Push a value on the top of this stack.
/// @param self A pointer to this stack.
/// @param value The value.
void
Ring2_Collections_Stack_push
  (
    Ring2_Collections_Stack* self,
    Ring2_Value value
  );


#endif // RING2_LIBRARY_COLLECTIONS_STACK_H_INCLUDED
