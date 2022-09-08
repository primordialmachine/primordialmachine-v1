/// @file Collections/Deque.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_DEQUE_H_INCLUDED)
#define MACHINE_COLLECTIONS_DEQUE_H_INCLUDED

#include "Collections/_header.i"

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

#endif // MACHINE_COLLECTIONS_DEQUE_H_INCLUDED
