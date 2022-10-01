// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collection.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Collection.h"
#undef RING2_LIBRARY_PRIVATE


MACHINE_DEFINE_INTERFACETYPE(Machine_Collection, NULL)

void
Machine_Collection_clear
  (
    Machine_Collection* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Machine_Collection, clear, , self); }

Ring1_CheckReturn() int64_t
Machine_Collection_getSize
  (
    Machine_Collection const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Machine_Collection, getSize, return, self); }

Ring1_CheckReturn() bool
Machine_Collection_isEmpty
  (
    Machine_Collection const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Machine_Collection, isEmpty, return, self); }
