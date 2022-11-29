// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/Collection.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Collection.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


MACHINE_DEFINE_INTERFACETYPE(Ring2_Collections_Collection, NULL)

void
Ring2_Collections_Collection_clear
  (
    Ring2_Collections_Collection* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Collection, clear, , self); }

Ring1_CheckReturn() int64_t
Ring2_Collections_Collection_getSize
  (
    Ring2_Collections_Collection const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Collection, getSize, return, self); }

Ring1_CheckReturn() Ring2_Boolean
Ring2_Collections_Collection_isEmpty
  (
    Ring2_Collections_Collection const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Collection, isEmpty, return, self); }
