// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/HashSet.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_HASHSET_H_INCLUDED)
#define RING2_LIBRARY_HASHSET_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/HashSet.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif

#include "Ring2/_Include.h"

/// The version of the Ring2.HashSet type implementation.
#define RING2_LIBRARY_HASHSET_VERSION (2)

/// @brief A hash based set of values.
/// @remark
/// The hash map supports the operations
/// - "get" (Mkx_Interpreter_Library_HashSet_get),
/// - "add" (Mkx_Interpreter_Library_HashSet_add), and
/// - "remove" (Mkx_Interpreter_Library_HashSet_remove).
/// @remark
/// Hash sets support the equal (by reference), not equal (by reference), and hash value (hash reference) operations.
MACHINE_DECLARE_CLASSTYPE(Machine_HashSet)

void
Machine_HashSet_construct
  (
    Machine_HashSet *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a hash set.
/// @return The hash set.
Machine_HashSet *
Machine_HashSet_create
  (
  );

/// @brief Add a value to this hash set.
/// @param self This hash set.
/// @param value The value.
/// @post The value @a value exists in this hash set.
/// @remark
/// If an equivalent value exists, then that value is replaced by the specified value.
/// If the specified value is the void value, then this call is a no operation.
void
Machine_HashSet_add
  (
    Machine_HashSet* self,
    Ring2_Value value
  );

/// @brief Get a value from this hash set.
/// @param self This hash set.
/// @param value The value.
/// @return A value equivalent to @a value if it exists in this hash set, a <code>Void</code> value otherwise.
Ring2_Value
Machine_HashSet_get
  (
    Machine_HashSet* self,
    Ring2_Value value
  );
  
/// @brief Remove a value from this hash set.
/// @param self This hash set.
/// @param value The value.
/// @post No value equivalent to @a value exists in this hash set.
/// @remark If @a value is a <code>Void</code> value, then this call is a no operation.
void
Machine_HashSet_remove
  (
    Machine_HashSet* self,
    Ring2_Value value
  );

/// @brief Clear this hash set.
/// @param self This hash set.
void
Machine_HashSet_clear
  (
    Machine_HashSet* self
  );

/// @brief Get the size of this hash set.
/// @param self This hash set.
/// @return The size.
int64_t
Machine_HashSet_getSize
  (
    Machine_HashSet* self
  );

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
/// @brief Get the values.
/// @param self This hash set.
/// @return An array.
/// The elements represent the values in this hash set.
Ring2_Array*
Machine_HashSet_getEntries
  (
    Machine_HashSet* self
  );
#endif

#endif // RING2_LIBRARY_HASHSET_H_INCLUDED
