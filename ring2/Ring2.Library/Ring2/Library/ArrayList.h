// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ArrayList.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_ARRAYLIST_H_INCLUDED)
#define RING2_LIBRARY_ARRAYLIST_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/ArrayList.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @brief An array list
/// @remark
/// Array lists support the equal (by reference), not equal (by reference), and hash value (hash reference) operations.
MACHINE_DECLARE_CLASSTYPE(Ring2_ArrayList)

void
Ring2_ArrayList_construct
  (
    Ring2_ArrayList *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create an array.
/// @return The array.
Ring2_ArrayList *
Ring2_ArrayList_create
  (
  );


#endif // RING2_LIBRARY_ARRAYLIST_H_INCLUDED
