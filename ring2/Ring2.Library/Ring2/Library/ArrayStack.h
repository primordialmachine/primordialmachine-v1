// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ArrayStack.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_ARRAYSTACK_H_INCLUDED)
#define RING2_LIBRARY_ARRAYSTACK_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/ArrayStack.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// The version of the Ring2.Library.ArrayStack type implementation.
#define RING2_LIBRARY_ARRAYSTACK_VERSION (2)

/// @brief A stack.
MACHINE_DECLARE_CLASSTYPE(Machine_ArrayStack)

void
Machine_ArrayStack_construct
  (
    Machine_ArrayStack *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a stack.
/// @return The stack.
Machine_ArrayStack *
Machine_ArrayStack_create
  (
  );

/// @brief Push a value on the top of this stack.
/// @param value The value.
void
Machine_ArrayStack_push
  (
    Machine_ArrayStack* self,
    Ring2_Value value
  );

/// @brief Pop the value on top of this stack.
/// @param self This stack.
/// @return The value.
Ring2_Value
Machine_ArrayStack_pop
  (
    Machine_ArrayStack* self
  );


#endif // RING2_LIBRARY_ARRAYSTACK_H_INCLUDED
