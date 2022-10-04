// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collection.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Collection.h"
#undef RING2_LIBRARY_PRIVATE


MACHINE_DEFINE_INTERFACETYPE(Ring2_Collection, NULL)

void
Ring2_Collection_clear
  (
    Ring2_Collection* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collection, clear, , self); }

Ring1_CheckReturn() int64_t
Ring2_Collection_getSize
  (
    Ring2_Collection const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collection, getSize, return, self); }

Ring1_CheckReturn() bool
Ring2_Collection_isEmpty
  (
    Ring2_Collection const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collection, isEmpty, return, self); }
