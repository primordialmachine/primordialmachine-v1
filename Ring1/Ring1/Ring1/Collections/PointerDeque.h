// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Collections/PointerDeque.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_COLLECTIONS_POINTERDEQUE_H_INCLUDED)
#define RING1_COLLECTIONS_POINTERDEQUE_H_INCLUDED


#include "Ring1/Collections/_Include.h"
#include "Ring1/Module.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_Module_Declare(Ring1, PointerDeque)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_Capacity_Least
#define Ring1_PointerDeque_Capacity_Least (8)

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_Capacity_Default
#define Ring1_PointerDeque_Capacity_Default (8)

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_Capacity_Greatest
#define Ring1_PointerDeque_Capacity_Greatest ((SIZE_MAX < INT64_MAX ? SIZE_MAX : INT64_MAX) / sizeof(void *))

// Perform some sanity checks on the capacity values.
static_assert(Ring1_PointerDeque_Capacity_Least <= Ring1_PointerDeque_Capacity_Greatest,
              "least capacity must be smaller than or equal to greatest capacity");
static_assert(Ring1_PointerDeque_Capacity_Least <= Ring1_PointerDeque_Capacity_Default &&
              Ring1_PointerDeque_Capacity_Default <= Ring1_PointerDeque_Capacity_Greatest,
              "default capacity must be a) greater than or equal least capacity and b) smaller than or equal to greatest capacity");


/// @brief A deque of pointers.
/// @remark Implemented using the PIMPL idiom.
/// Supports null pointers.
typedef struct Ring1_PointerDeque { void *pimpl; } Ring1_PointerDeque;

/// @brief Initialize a pointer deque.
/// @param pointerDeque A pointer to an uninitialized pointer deque.
/// @param added A pointer to an added callback function or a null pointer.
/// @param removed A pointer to a removed callback function or a null pointer.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_initialize
  (
    Ring1_PointerDeque *pointerDeque,
    int64_t initialCapacity,
    Ring1_AddedCallback *add,
    Ring1_RemovedCallback *remove
  );

/// @brief Uninitialize a pointer deque.
/// @param pointerDeque A pointer to an initialized pointer deque.
void
Ring1_PointerDeque_uninitialize
  (
    Ring1_PointerDeque *pointerDeque
  );

/// @brief Increase the capacity of a pointer deque by at least the specified amount.
/// @param pointerDeque A pointer to a pointer deque.
/// @param requiredAdditionalCapacity The amount to increase the capacity at least by. Must be non-negative.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
/// @post The capacity was increased by at least the specified amount on success. On failure, the deque was not observably modified.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_increaseCapacity
  (
    Ring1_PointerDeque *pointerDeque,
    int64_t requiredAdditionalCapacity
  );

/// @brief "where" on a pointer deque.
/// @param pointerDeque A pointer to the pointer deque.
/// @param whereContext A pointer passed as the "where" context to the "where" callback.
/// @param whereCallback A pointer to a "where" callback function.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
/// @remark
/// Elements for which the "where" callback returns @a true remains in the collection.
/// Other elements are removed.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_filter
  (
    Ring1_PointerDeque* pointerDeque,
    Ring1_WhereContext* whereContext,
    Ring1_WhereCallback* whereCallback
  );

/// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_ensurefreeCapacity
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_ensureFreeCapacity
  (
    Ring1_PointerDeque *pointerDeque,
    int64_t requiredFreeCapacity
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_getSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_getSize
  (
    int64_t *size,
    Ring1_PointerDeque *pointerDeque
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_getCapacity
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_getCapacity
  (
    int64_t *capacity,
    Ring1_PointerDeque *pointerDeque
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_getFreeCapacity
Ring1_NoDiscardReturn() int64_t
Ring1_PointerDeque_getFreeCapacity
  (
    Ring1_PointerDeque *pointerDeque
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_clear
Ring1_Result
Ring1_PointerDeque_clear
  (
    Ring1_PointerDeque *pointerDeque
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_insertAt
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_insertAt
  (
    Ring1_PointerDeque* pointerDeque,
    int64_t index,
    void* pointer
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_insertBack
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_insertBack
  (
    Ring1_PointerDeque *pointerDeque,
    void *pointer
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_insertFront
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_insertFront
  (
    Ring1_PointerDeque *pointerDeque,
    void *pointer
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerDeque_getAt
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_getAt
  (
    Ring1_PointerDeque *pointerDeque,
    int64_t index,
    void **element
  );

/// @brief Remove the element at the specified index.
/// @param pointerDeque A pointer to the pointer deque.
/// @param index The index of the element to be removed.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @remark If a Ring1_RemovedCallback is specified, it is invoked on the element.
/// @error #Ring1_Status_IsEmpty the deque is empty.
/// @error #Ring1_Status_IndexOutOfBounds @a index is negative or greater than or equal the size of the queue.
/// @error #Ring1_Status_InvalidArgument @a pointerDeque is a null pointer.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_removeAt
  (
    Ring1_PointerDeque *pointerDeque,
    int64_t index,
    void **element
  );

/// @brief Steal the element at the specified index.
/// @param pointerDeque A pointer to the pointer deque.
/// @param index The index of the element to be removed.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @remark
/// Unlike Ring1_PointerDeque_removeAt,
/// the associated Ring1_RemovedCallback is not invoked on the element.
/// @error #Ring1_Status_IsEmpty the deque is empty.
/// @error #Ring1_Status_IndexOutOfBounds @a index is negative or greater than or equal the size of the queue.
/// @error #Ring1_Status_InvalidArgument @a pointerDeque is a null pointer.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_stealAt
  (
    Ring1_PointerDeque* pointerDeque,
    int64_t index,
    void** element
  );

/// @brief
/// <code>Ring1_PointerDeque_removeFront(c,e)</code>
/// is equivalent to
/// <code>Ring1_PointerDeque_removeAt(c,0,e)</code>.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @remark If a Ring1_RemovedCallback is specified, it is invoked on the element.
/// @error #Ring1_Status_IsEmpty the deque is empty.
/// @error #Ring1_Status_InvalidArgument @a pointerDeque is a null pointer.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_removeFront
  (
    Ring1_PointerDeque* pointerDeque,
    void** element
  );

/// @brief
/// <code>Ring1_PointerDeque_stealFront(c,e)</code>
/// is equivalent to
/// <code>Ring1_PointerDeque_stealAt(c,0,e)</code>.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @remarks
/// Unlike Ring1_PointerDeque_removeAt,
/// the associated Ring1_RemovedCallback is not invoked on the element.
/// @error #Ring1_Status_IsEmpty the deque is empty.
/// @error #Ring1_Status_InvalidArgument @a pointerDeque is a null pointer.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_stealFront
  (
    Ring1_PointerDeque* pointerDeque,
    void** element
  );


#endif // RING1_COLLECTIONS_POINTERDEQUE_H_INCLUDED
