// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/HashMap.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_COLLECTIONS_HASHMAP_H_INCLUDED)
#define RING2_LIBRARY_COLLECTIONS_HASHMAP_H_INCLUDED


#if !defined(RING2_LIBRARY_COLLECTIONS_PRIVATE) || 1 != RING2_LIBRARY_COLLECTIONS_PRIVATE
#error("Do not include `Ring2/Library/Collections/HashMap.h` directly. Include `Ring2/Library/Collections/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @implements Ring2.Collections.Map
/// @brief A hash based map from keys to values.
MACHINE_DECLARE_CLASSTYPE(Ring2_Collections_HashMap)

void
Ring2_Collections_HashMap_construct
  (
    Ring2_Collections_HashMap *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a hash map.
/// @return The hash map.
Ring2_Collections_HashMap *
Ring2_Collections_HashMap_create
  (
  );


#endif // RING2_LIBRARY_COLLECTIONS_HASHMAP_H_INCLUDED
