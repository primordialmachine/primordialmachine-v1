// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/Set.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_COLLECTIONS_SET_H_INCLUDED)
#define RING2_LIBRARY_COLLECTIONS_SET_H_INCLUDED


#if !defined(RING2_LIBRARY_COLLECTIONS_PRIVATE) || 1 != RING2_LIBRARY_COLLECTIONS_PRIVATE
#error("Do not include `Ring2/Library/Collections/Set.h` directly, include `Ring2/Library/Collections/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"
typedef struct Ring2_Collections_List Ring2_Collections_List;


/// @extends Ring2.Collections.Collection
MACHINE_DECLARE_INTERFACETYPE(Ring2_Collections_Set)

struct Ring2_Collections_Set_Dispatch {
  Machine_InterfaceDispatch parent;

  void (*add)(Ring2_Collections_Set* self, Ring2_Value value);
  Ring2_Boolean (*contains)(Ring2_Collections_Set const* self, Ring2_Value value);
  void (*remove)(Ring2_Collections_Set* self, Ring2_Value value);
  Ring2_Collections_List* (*toList)(Ring2_Collections_Set const* self);
};

/// @brief Insert a value into this set.
/// @details
/// Ensures <code>v in S</code> where
/// - <code>S</code> is this set and
/// - <code>v != void</code> is the value.
/// If an equivalent value exists in this set,
/// then this value is replaced by the specified value.
/// 
/// If <code>v</code> is a <code>Void</code> value,
/// then this is a no operation.
/// 
/// @param self This set.
/// @param value The value.
void
Ring2_Collections_Set_add
  (
    Ring2_Collections_Set* self,
    Ring2_Value value
  );

/// @brief Remove a value from this set.
/// @tdetails
/// Ensures <code>V in S</code> where
/// - <code>S</code> is th set and
/// - <code>v != void</code> is the value.
/// If an equivalent value exists in this set,
/// then this value is removed.
/// 
/// If @a value is a <code>Void</code> value, then this call is a no operation.
/// 
/// @param self This set.
/// @param value The value.
/// @post No value equivalent to @a value exists in this hash set.
void
Ring2_Collections_Set_remove  
  (
    Ring2_Collections_Set* self,
    Ring2_Value value
  );

/// @brief Get if a value equivalent to a specified value is contained in the set.
/// @param self This set.
/// @param v The key.
/// @return
/// @a true if a value equivalent to the specified value @a v is contained in the set.
/// @a false otherwise.
Ring2_Boolean
Ring2_Collections_Set_contains
  (
    Ring2_Collections_Set const* self,
    Ring2_Value v
  );

/// @brief Convert the specified set to a list of values.
/// @param self This set.
/// @return The list of values.
Ring2_Collections_List*
Ring2_Collections_Set_toList
  (
    Ring2_Collections_Set const* self
  );


#endif // RING2_LIBRARY_COLLECTIONS_SET_H_INCLUDED
