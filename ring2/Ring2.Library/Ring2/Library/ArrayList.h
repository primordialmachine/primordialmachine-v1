// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ArrayList.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_ARRAYLIST_H_INCLUDED)
#define RING2_LIBRARY_ARRAYLIST_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/ArrayList.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif

#include "Ring2/_Include.h"

/// The version of the Ring2.ArrayList type implementation.
#define RING2_LIBRARY_ARRAYLIST_VERSION (2)

/// @brief An array list
/// @remark
/// Array lists support the equal (by reference), not equal (by reference), and hash value (hash reference) operations.
MACHINE_DECLARE_CLASSTYPE(Machine_ArrayList)

void
Machine_ArrayList_construct
  (
    Machine_ArrayList *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create an array.
/// @return The array.
Machine_ArrayList *
Machine_ArrayList_create
  (
  );

#endif // RING2_LIBRARY_ARRAYLIST_H_INCLUDED
