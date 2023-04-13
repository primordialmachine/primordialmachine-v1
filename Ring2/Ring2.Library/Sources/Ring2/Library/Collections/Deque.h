// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/Deque.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_COLLECTIONS_DEQUE_H_INCLUDED)
#define RING2_LIBRARY_COLLECTIONS_DEQUE_H_INCLUDED


#if !defined(RING2_LIBRARY_COLLECTIONS_PRIVATE) || 1 != RING2_LIBRARY_COLLECTIONS_PRIVATE
#error("Do not include `Ring2/Library/Collections/Deque.h` directly. Include `Ring2/Library/Collections/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @extends Ring2.Collections.Collection
/// @brief A double-ended queue.
/// @details Supports fast insertion and removal at its both ends.
MACHINE_DECLARE_INTERFACETYPE(Ring2_Collections_Deque)

struct Ring2_Collections_Deque_Dispatch {
  Machine_InterfaceDispatch parent;

  void (*pushFront)(Ring2_Collections_Deque* self, Ring2_Value value);
  Ring2_Value (*popFront)(Ring2_Collections_Deque* self);
  void (*pushBack)(Ring2_Collections_Deque* self, Ring2_Value value);
  Ring2_Value (*popBack)(Ring2_Collections_Deque* self);
};

/// @brief Dequeue a value from the front of this deque.
/// @param self This deque.
/// @return The value.
Ring2_Value
Ring2_Collections_Deque_popFront
  (
    Ring2_Collections_Deque* self
  );

/// @brief Enqueue a value to the front of this deque.
/// @param self This deque.
/// @param value The value.
void
Ring2_Collections_Deque_pushFront
  (
    Ring2_Collections_Deque* self,
    Ring2_Value value
  );

/// @brief Dequeue a value from thhe back of this deque.
/// @param self This deque.
/// @return The value.
Ring2_Value
Ring2_Collections_Deque_popBack
  (
    Ring2_Collections_Deque* self
  );

/// @brief Enqueue a value to the back of this deque.
/// @param self This deque.
/// @param value The value.
void
Ring2_Collections_Deque_pushBack
  (
    Ring2_Collections_Deque* self,
    Ring2_Value value
  );


#endif // RING2_LIBRARY_COLLECTIONS_DEQUE_H_INCLUDED
