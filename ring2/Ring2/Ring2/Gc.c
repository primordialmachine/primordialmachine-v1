// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Gc.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Gc.h"

#define RING2_GC_PRIVATE
#include "Ring2/Gc/Implementation/Gc1.h"
#undef RING2_GC_PRIVATE

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_Gc_PreMarkCallbackId
Ring2_Gc_addPreMarkCallback
  (
    Ring2_Gc* gc,
    void* object,
    Ring2_Gc_PreMarkCallback* callback
  )
{ return Ring2_Gc_Implementation_Gc1_addPreMarkCallback((Ring2_Gc_Implementation_Gc1*)gc, object, callback); }

void
Ring2_Gc_removePreMarkCallback
  (
    Ring2_Gc* gc,
    Ring2_Gc_PreMarkCallbackId id
  )
{ Ring2_Gc_Implementation_Gc1_removePreMarkCallback((Ring2_Gc_Implementation_Gc1*)gc, id); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_Gc_SweepCallbackId
Ring2_Gc_addSweepCallback
  (
    Ring2_Gc* gc,
    void* object,
    Ring2_Gc_SweepCallback* callback
  )
{ return Ring2_Gc_Implementation_Gc1_addSweepCallback((Ring2_Gc_Implementation_Gc1*)gc, object, callback); }

void
Ring2_Gc_removeSweepCallback
  (
    Ring2_Gc* gc,
    Ring2_Gc_SweepCallbackId id
  )
{ Ring2_Gc_Implementation_Gc1_removeSweepCallback((Ring2_Gc_Implementation_Gc1*)gc, id); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_Gc*
Ring2_Gc_create
  (
  )
{ return (Ring2_Gc *)Ring2_Gc_Implementation_Gc1_create(); }

void
Ring2_Gc_destroy
  (
    Ring2_Gc *gc
  )
{ Ring2_Gc_Implementation_Gc1_destroy((Ring2_Gc_Implementation_Gc1 *)gc); }

void*
Ring2_Gc_allocate
  (
    Ring2_Gc* gc,
    size_t size,
    Ring2_Gc_Type const* type,
    Ring2_Gc_Tag** objectList
  )
{
  return Ring2_Gc_Implementation_Gc1_allocate((Ring2_Gc_Implementation_Gc1*)gc, size, type, objectList);
}

Ring2_Gc_Tag*
Ring2_Gc_toTag
  (
    void* x
  )
{ return Ring2_Gc_Implementation_Gc1_toTag(x); }

void*
Ring2_Gc_toAddress
  (
    Ring2_Gc_Tag* x
  )
{ return Ring2_Gc_Implementation_Gc1_toAddress(x); }

void
Ring2_Gc_visit
  (
    Ring2_Gc* gc,
    void *address
  )
{ Ring2_Gc_Implementation_Gc1_visit((Ring2_Gc_Implementation_Gc1*)gc, address); }

void
Ring2_Gc_run
  (
    Ring2_Gc* gc,
    Ring2_Gc_RunStatistics *statistics
  )
{ Ring2_Gc_Implementation_Gc1_run((Ring2_Gc_Implementation_Gc1 *)gc, statistics); }
