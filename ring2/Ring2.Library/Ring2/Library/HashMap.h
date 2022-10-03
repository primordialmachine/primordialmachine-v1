// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/HashMap.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_HASHMAP_H_INCLUDED)
#define RING2_LIBRARY_HASHMAP_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/HashMap.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// The version of the Ring2.HashMap type implementation.
#define RING2_LIBRARY_HASHMAP_VERSION (2)

/// @brief A hash based map from keys to values.
/// @remark
/// The hash map supports the operations
/// - "get" (Mkx_Interpreter_Library_HashMap_get),
/// - "set" (Mkx_Interpreter_Library_HashMap_set), and
/// - "remove" (Mkx_Interpreter_Library_HashMap_remove).
/// @remark
/// Hash maps support the equal (by reference), not equal (by reference), and hash value (hash reference) operations.
MACHINE_DECLARE_CLASSTYPE(Machine_HashMap)

void
Machine_HashMap_construct
  (
    Machine_HashMap *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a hash map.
/// @return The hash map.
Machine_HashMap *
Machine_HashMap_create
  (
  );

/// @brief Remove an association.
/// @param self This hash map.
/// @param key The key.
void
Machine_HashMap_remove
  (
    Machine_HashMap* self,
    Ring2_Value key
  );


#endif // RING2_LIBRARY_HASHMAP_H_INCLUDED
