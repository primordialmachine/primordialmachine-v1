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
MACHINE_DECLARE_CLASSTYPE(Ring2_ArrayStack)

void
Ring2_ArrayStack_construct
  (
    Ring2_ArrayStack *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a stack.
/// @return The stack.
Ring2_ArrayStack *
Ring2_ArrayStack_create
  (
  );


#endif // RING2_LIBRARY_ARRAYSTACK_H_INCLUDED
