// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/List.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/List.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Collection.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


static void addPrerequisites(Machine_InterfaceType* self){
  Machine_InterfaceType_extend(self, (Machine_Type *)Ring2_Collections_Collection_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Ring2_Collections_List, &addPrerequisites)

Ring2_Value
Ring2_Collections_List_getAt
  (
    Ring2_Collections_List const* self,
    int64_t index
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_List, getAt, return, self, index); }

void
Ring2_Collections_List_prepend
  (
    Ring2_Collections_List* self,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_List, prepend, , self, value); }

void
Ring2_Collections_List_append
  (
    Ring2_Collections_List* self,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_List, append, , self, value); }

void
Ring2_Collections_List_insertAt
  (
    Ring2_Collections_List* self,
    int64_t index,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_List, insertAt, , self, index, value); }

void
Ring2_Collections_List_removeAt
  (
    Ring2_Collections_List* self,
    int64_t index
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_List, removeAt, , self, index); }

void
Ring2_Collections_List_removeAtFast
  (
    Ring2_Collections_List* self,
    int64_t index
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_List, removeAtFast, , self, index); }

#if defined(Ring2_Collections_List_withReverse) && Ring2_Collections_List_withReverse == 1

void
Ring2_Collections_List_reverse
  (
    Ring2_Collections_List* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_List, reverse, , self); }

#endif

#if defined(Ring2_Collections_List_withSlice) && Ring2_Collections_List_withSlice == 1

Ring2_Collections_List*
Ring2_Collections_List_slice
  (
    Ring2_Collections_List* self,
    int64_t start,
    int64_t length
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_List, slice, return, self, start, length); }

#endif
