// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Collections/PointerList.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_COLLECTIONS_POINTERLIST_H_INCLUDED)
#define RING1_COLLECTIONS_POINTERLIST_H_INCLUDED


#include "Ring1/Collections/Callbacks.h"
#include "Ring1/Module.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_Module_Declare(Ring1, PointerList)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_Capacity_Least
#define Ring1_PointerList_Capacity_Least (0)

// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_Capacity_Default
#define Ring1_PointerList_Capacity_Default (8)

// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_Cpacity_Greatest
#define Ring1_PointerList_Capacity_Greatest ((SIZE_MAX < INT64_MAX ? SIZE_MAX : INT64_MAX) / sizeof(void *))

// Perform some sanity checks on the capacity values.
static_assert(Ring1_PointerList_Capacity_Least <= Ring1_PointerList_Capacity_Greatest,
              "least capacity must be smaller than or equal to greatest capacity");
static_assert(Ring1_PointerList_Capacity_Least <= Ring1_PointerList_Capacity_Default,
              "default capacity must be greater than or equal to least capacity");
static_assert(Ring1_PointerList_Capacity_Default <= Ring1_PointerList_Capacity_Greatest,
              "default capacity must smaller than or equal to greatest capacity");

// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList
typedef struct Ring1_PointerList { void* pimpl; } Ring1_PointerList;

// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_visitcallback
typedef void (Ring1_PointerList_VisitCallback)(void* context, void* element);

/// @brief The type of a callback function invoked during the "FIND" operation on a list.
/// This callback is invoked for each element in the list exactly once with the specified opaque context pointer as its 1st argument and the list element as its 2nd argument
/// until the callback returns true.
/// @param context The opaque context pointer.
/// @param element The pointer.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @remark The function must not mutate the list.
typedef Ring1_Result (Ring1_PointerList_FindCallback)(bool *result, void* context, void* element);

/// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_initialize
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_initialize
  (
    Ring1_PointerList* self,
    Ring1_AddedCallback *added,
    Ring1_RemovedCallback *removed
  );

/// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_uninitialize
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_uninitialize
  (
    Ring1_PointerList* self
  );

/// @brief Search an element in a pointer list.
/// @param index The index of the element to start at.
/// @param context An opaque context pointer passed to the Ring1_PointerList_FindCallback.
/// @param findCallback A pointer to a Ring1_PointerList_FindCallback function.
/// @param position A pointer to an int variable receiving the position on success.
/// If this function succeeds and the element was not found, the variable is assigned -1.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_find
  (
    Ring1_PointerList* pointerList,
    int64_t start,
    void *context,
    Ring1_PointerList_FindCallback* function,
    int64_t *occurrence
  );

void
Ring1_PointerList_visit
  (
    Ring1_PointerList* pointerList,
    void* context,
    Ring1_PointerList_VisitCallback *function
  );

/// @brief Filter on a pointer list.
/// @param pointerList A pointer to the pointer list.
/// @param whereContext A pointer passed as the "where" context to the "where" callback.
/// @param whereCallback A pointer to a "where" callback function.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @remark
/// Elements for which the "where" callback returns @a true remains in the collection.
/// Other elements are removed.
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_filter
  (
    Ring1_PointerList* pointerList,
    Ring1_WhereContext* whereContext,
    Ring1_WhereCallback* whereCallback
  );

// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_clear 
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_clear
  (
    Ring1_PointerList* self
  );

// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_insertAt
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_insertAt
  (
    Ring1_PointerList* self,
    int64_t index,
    void* element
  );

// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_insertBack
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_insertBack
  (
    Ring1_PointerList* self,
    void* element
  );

// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_insertFront
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_insertFront
  (
    Ring1_PointerList* self,
    void* element
  );

// https://primordialmachine.com/api/ring1-library/pointerlist-library/Ring1_PointerList_getAt
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_getAt
  (
    Ring1_PointerList* self,
    int64_t index,
    void** element
  );

/// @brief Remove the element at the specified index.
/// @param pointerList A pointer to the pointer list.
/// @param index The index of the element to be removed.
/// @remark If a Ring1_PointerList_RemovedCallback is specified, it is invoked on the element.
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_removeAt
  (
    Ring1_PointerList* pointerList,
    int64_t index,
    void **element
  );

/// @brief Steal the element at the specified index.
/// @param pointerList A pointer to the pointer list.
/// @param index The index of the element to be removed.
/// @remark Unlike Ring1_PointerList_removeAt, the Ring1_PointerList_RemovedCallback is not invoked on the element.
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_stealAt
  (
    Ring1_PointerList* seöf,
    int64_t index,
    void **element
  );

/// @return
/// - Ring1_PointerList_Status_Empty if the queue is empty.
/// Another non-zero status code on failure.
/// @remark If a Ring1_PointerList_RemovedCallback is specified, it is invoked on the element.
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_removeBack
  (
    Ring1_PointerList* self,
    void** element
  );

/// @return
/// - Ring1_PointerList_Status_Empty if the queue is empty.
/// Another non-zero status code on failure.
/// @remark Unlike Ring1_PointerList_removeBack, the Ring1_PointerList_RemovedCallback is not invoked on the element.
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_stealBack
  (
    Ring1_PointerList* self,
    void** element
  );

// https://documentation.primordialmachine.com/utility-library/pointerlist-library#Ring1_pointerlist_getsize
Ring1_CheckReturn() Ring1_Result
Ring1_PointerList_getSize
  (
    int64_t *result,
    Ring1_PointerList* self
  );


#endif // RING1_COLLECTIONS_POINTERLIST_H_INCLUDED
