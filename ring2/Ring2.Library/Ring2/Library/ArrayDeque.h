// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ArrayDeque.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_ARRAYDEQUE_H_INCLUDED)
#define RING2_LIBRARY_ARRAYDEQUE_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/ArrayDeque.h` directly. Include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


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
MACHINE_DECLARE_CLASSTYPE(Ring2_ArrayDeque)

/// @brief Construct this queue.
/// @param self A pointer to this queue.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void
Ring2_ArrayDeque_construct
  (
    Ring2_ArrayDeque* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create an empty queue.
/// @return The queue.
Ring2_ArrayDeque*
Ring2_ArrayDeque_create
  (
  );


#endif // RING2_LIBRARY_ARRAYDEQUE_H_INCLUDED
