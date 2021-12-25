/// @file Collections/ArrayDeque.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_ARRAYDEQUE_H_INCLUDED)
#define MACHINE_COLLECTIONS_ARRAYDEQUE_H_INCLUDED

#include "Collections/_header.i"

/// @brief An array deque.
/// We have a write position WRITE and a rear position READ.
/// Both are initially 0.
///
/// We have a size SIZE and a capacity CAPACITY which is initially 0.
///
/// pushBack
/// First we check if the queue is full i.e. SIZE == CAPACITY.
/// If the queue is full, we increase the capacity such that SIZE < CAPACITY.
/// We store the element at e[(TAIL + 1) % CAPACITY] and then let TAIL' = (TAIL + 1) % CAPACITY and
/// SIZE' = SIZE + 1.
///
/// pushFront
/// First we check if the queue is full i.e. SIZE == CAPACITY.
/// If the queue is full, we increase the capacity such that SIZE < CAPACITY.
/// We store the element at e[(HEAD - 1) % CAPACITY] and then let HEAD' = (HEAD - 1) % CAPACITY and
/// SIZE' = SIZE + 1.
MACHINE_DECLARE_CLASSTYPE(Machine_ArrayDeque)

struct Machine_ArrayDeque_Class {
  Machine_Object_Class parent;
};

struct Machine_ArrayDeque {
  Machine_Object parent;
  /// @brief The size of the queue.
  size_t size;
  /// @brief The capacity of the queue.
  /// @initial @a 0.
  size_t capacity;
  /// @brief The head of the queue.
  /// @initial @a 0.
  size_t head;
  /// @brief The tail of the queue.
  /// @initial @a 0.
  size_t tail;
  /// @brief A pointer to an array of @a capacity Machine_Value elements.
  Machine_Value* elements;
};

/// @brief Construct this queue.
/// @param self A pointer to this queue.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_ArrayDeque_construct(Machine_ArrayDeque* self, size_t numberOfArguments,
                                  Machine_Value const* arguments);

/// @brief Create an empty queue.
/// @return The queue.
Machine_ArrayDeque* Machine_ArrayDeque_create();

#endif // MACHINE_COLLECTIONS_ARRAYDEQUE_H_INCLUDED
