// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/ArrayStack.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_COLLECTIONS_ARRAYSTACK_H_INCLUDED)
#define RING2_LIBRARY_COLLECTIONS_ARRAYSTACK_H_INCLUDED


#if !defined(RING2_LIBRARY_COLLECTIONS_PRIVATE) || 1 != RING2_LIBRARY_COLLECTIONS_PRIVATE
#error("Do not include `Ring2/Library/Collections/ArrayStack.h` directly. Include `Ring2/Library/Collections/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @implements Ring2.Collections.Stack
/// @brief A stack.
MACHINE_DECLARE_CLASSTYPE(Ring2_Collections_ArrayStack)

void
Ring2_Collections_ArrayStack_construct
  (
    Ring2_Collections_ArrayStack *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a stack.
/// @return The stack.
Ring2_Collections_ArrayStack *
Ring2_Collections_ArrayStack_create
  (
  );


#endif // RING2_LIBRARY_COLLECTIONS_ARRAYSTACK_H_INCLUDED
