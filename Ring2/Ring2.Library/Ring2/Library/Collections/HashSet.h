// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/HashSet.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_COLLECTIONS_HASHSET_H_INCLUDED)
#define RING2_LIBRARY_COLLECTIONS_HASHSET_H_INCLUDED


#if !defined(RING2_LIBRARY_COLLECTIONS_PRIVATE) || 1 != RING2_LIBRARY_COLLECTIONS_PRIVATE
#error("Do not include `Ring2/Library/Collections/HashSet.h` directly. Include `Ring2/Library/Collections/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @implements Ring2.Collections.Set
/// @brief A hash based set of values.
MACHINE_DECLARE_CLASSTYPE(Ring2_Collections_HashSet)

void
Ring2_Collections_HashSet_construct
  (
    Ring2_Collections_HashSet *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a hash set.
/// @return The hash set.
Ring2_Collections_HashSet *
Ring2_Collections_HashSet_create
  (
  );


#endif // RING2_LIBRARY_COLLECTIONS_HASHSET_H_INCLUDED
