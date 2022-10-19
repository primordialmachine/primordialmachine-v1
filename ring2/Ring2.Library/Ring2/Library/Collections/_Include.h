// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_COLLECTIONS__INCLUDE_H_INCLUDED)
#define RING2_LIBRARY_COLLECTIONS__INCLUDE_H_INCLUDED

#pragma push_macro("RING2_LIBRARY_PRIVATE")
#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/ArrayDeque.h"
#include "Ring2/Library/Collections/ArrayList.h"
#include "Ring2/Library/Collections/ArrayStack.h"
#include "Ring2/Library/Collections/Collection.h"
#include "Ring2/Library/Collections/Deque.h"
#include "Ring2/Library/Collections/HashMap.h"
#include "Ring2/Library/Collections/HashSet.h"
#include "Ring2/Library/Collections/List.h"
#include "Ring2/Library/Collections/Map.h"
#include "Ring2/Library/Collections/Pair.h"
#include "Ring2/Library/Collections/Set.h"
#include "Ring2/Library/Collections/Stack.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE
#pragma pop_macro("RING2_LIBRARY_PRIVATE")

#endif // RING2_LIBRARY_COLLECTIONS__INCLUDE_H_INCLUDED
