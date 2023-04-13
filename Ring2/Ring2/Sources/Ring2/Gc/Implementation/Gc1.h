// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Gc/Implementation/Gc1.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

/// @brief A precise, non-incremental, mark-and-sweep GC.

#if !defined(RING2_GC_IMPLEMENTATION_GC1_H_INCLUDED)
#define RING2_GC_IMPLEMENTATION_GC1_H_INCLUDED

#include "Ring2/Gc/Configuration.h"
#include "Ring2/Gc.h"




typedef struct Ring2_Gc_Implementation_Gc1 Ring2_Gc_Implementation_Gc1;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_Gc_PreMarkCallbackId
Ring2_Gc_Implementation_Gc1_addPreMarkCallback
  (
    Ring2_Gc_Implementation_Gc1* gc,
    void* object,
    Ring2_Gc_PreMarkCallback* callback
  );

void
Ring2_Gc_Implementation_Gc1_removePreMarkCallback
  (
    Ring2_Gc_Implementation_Gc1* gc,
    Ring2_Gc_PreMarkCallbackId id
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_Gc_SweepCallbackId
Ring2_Gc_Implementation_Gc1_addSweepCallback
  (
    Ring2_Gc_Implementation_Gc1* gc,
    void* object,
    Ring2_Gc_SweepCallback* callback
  );

void
Ring2_Gc_Implementation_Gc1_removeSweepCallback
  (
    Ring2_Gc_Implementation_Gc1* gc,
    Ring2_Gc_SweepCallbackId id
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring2_Gc_Implementation_Gc1 *
Ring2_Gc_Implementation_Gc1_create
  (
  );

void
Ring2_Gc_Implementation_Gc1_destroy
  (
    Ring2_Gc_Implementation_Gc1 *gc
  );

void*
Ring2_Gc_Implementation_Gc1_allocate
  (
    Ring2_Gc_Implementation_Gc1* gc,
    size_t size,
    Ring2_Gc_Type const*type,
    Ring2_Gc_Tag **objectList
  );

void
Ring2_Gc_Implementation_Gc1_run
  (
    Ring2_Gc_Implementation_Gc1* gc,
    Ring2_Gc_RunStatistics *statistics
  );

Ring2_Gc_Tag*
Ring2_Gc_Implementation_Gc1_toTag
  (
    void* x
  );

void*
Ring2_Gc_Implementation_Gc1_toAddress
  (
    Ring2_Gc_Tag* x
  );

void
Ring2_Gc_Implementation_Gc1_visit
  (
    Ring2_Gc_Implementation_Gc1* gc,
    void *address
  );

#endif // RING2_GC_IMPLEMENTATION_GC1_H_INCLUDED
