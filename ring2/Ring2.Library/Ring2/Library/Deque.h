// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Deque.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_DEQUE_H_INCLUDED)
#define RING2_LIBRARY_DEQUE_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Deque.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @brief A double-ended queue.
/// @details Supports fast insertion and removal at its both ends.
MACHINE_DECLARE_INTERFACETYPE(Machine_Deque)

struct Machine_Deque_Dispatch {
  Machine_InterfaceDispatch parent;

  void (*pushFront)(Machine_Deque* self, Ring2_Value value);
  Ring2_Value (*popFront)(Machine_Deque* self);
  void (*pushBack)(Machine_Deque* self, Ring2_Value value);
  Ring2_Value (*popBack)(Machine_Deque* self);
};

/// @brief Dequeue a value from the front of this deque.
/// @param self This deque.
/// @return The value.
Ring2_Value Machine_Deque_popFront(Machine_Deque* self);

/// @brief Enqueue a value to the front of this deque.
/// @param self This deque.
/// @param value The value.
void Machine_Deque_pushFront(Machine_Deque* self, Ring2_Value value);

/// @brief Dequeue a value from thhe back of this deque.
/// @param self This deque.
/// @return The value.
Ring2_Value Machine_Deque_popBack(Machine_Deque* self);

/// @brief Enqueue a value to the back of this deque.
/// @param self This deque.
/// @param value The value.
void Machine_Deque_pushBack(Machine_Deque* self, Ring2_Value value);


#endif // RING2_LIBRARY_DEQUE_H_INCLUDED
