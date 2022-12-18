// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Collections/Callbacks.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_COLLECTIONS_CALLBACKS_H_INCLUDED)
#define RING1_COLLECTIONS_CALLBACKS_H_INCLUDED


#include "Ring1/Intrinsic/_Include.h"
#include "Ring1/Status.h"
#include <stdbool.h>

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_AddedCallback
typedef void (Ring1_AddedCallback)(void* element);

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_GetHashCallback
typedef Ring1_Result (Ring1_GetHashCallback)(int64_t *result, void* element);

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_IsEqualToCallback
typedef Ring1_Result (Ring1_IsEqualToCallback)(bool* result, void* first, void *second);

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_RemovedCallback
typedef void (Ring1_RemovedCallback)(void* element);

/// @brief The type of a "where" predicate context.
typedef void Ring1_WhereContext;

/// @brief
/// The type of a "where" predicate callback function.
/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param context
/// A pointer to a "where" predicate context or a null pointer.
/// @param index
/// The index of the element.
/// @param element
/// Opaque pointer to the element.
/// @return
/// #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @success
/// <code>*result</code> was assigned <code>true</code> if the element is accepted by the predicate, otherwise it is assigned <code>false</code>.
/// @failure
/// <code>result</code> was not dereferenced.
typedef Ring1_Result (Ring1_WhereCallback)(bool* result, Ring1_WhereContext* context, int64_t index, void* element);

#endif // RING1_COLLECTIONS_CALLBACKS_H_INCLUDED
