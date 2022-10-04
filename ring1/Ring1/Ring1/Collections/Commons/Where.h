// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Collections/Commons/Where.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_COLLECTIONS_COMMONS_WHERE_H_INCLUDED)
#define MKX_COLLECTIONS_COMMONS_WHERE_H_INCLUDED


#include "Ring1/Intrinsic.h"
#include "Ring1/Status.h"
#include <stdbool.h>

/// @brief The type of a "where" predicate context.
typedef void Mkx_Collection_WherePredicateContext;

/// @brief The type of a "where" predicate callback function.
/// @param result A pointer to a <code>bool</code> variable.
/// @param context A pointer to a "where" predicate context or a null pointer.
/// @param index The index of the element.
/// @param element Opaque pointer to the element.
/// @return #Mkx_Status_Success on success, a failure status code on failure.
/// @success <code>*result</code> was assigned <code>true</code> if the element is accepted by the predicate,
/// otherwise it is assigned <code>false</code>.
/// @fawilure <code>result</code> was not dereferenced.
typedef Ring1_Status (Mkx_Collection_WherePredicateCallback)(bool* result, Mkx_Collection_WherePredicateContext* context, int64_t index, void* element);

#endif // MKX_COLLECTIONS_COMMONS_WHERE_H_INCLUDED
