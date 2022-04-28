// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Gc.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_GC_H_INCLUDED)
#define RING2_GC_H_INCLUDED

#include "Ring2/Gc/Type.h"
#include "Ring2/Gc/Tag.h"
#include "Ring2/Gc/RunStatistics.h"
#include "Ring2/Gc/SweepStatistics.h"
#include <stdint.h>


/// `typedef /*Implementation*/ Ring2_Interpreter_Gc`
/// The opaque type of a garbage collector.
typedef void Ring2_Gc;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// `#define Ring2_Gc_PreMarkCallbackId_Invalid /*Implementation*/`
/// Symbolic constant of the invalid premark callback ID.
/// Evaluates to `false` in boolean expressions.
#define Ring2_Gc_PreMarkCallbackId_Invalid ((uintptr_t)0)

/// `typedef /*Implementation*/ Ring2_Gc_PreMarkCallbackId`
/// Transparent type of a premark callback ID.
typedef uintptr_t Ring2_Gc_PreMarkCallbackId;

/// Type of a "premark" callback.
typedef void (Ring2_Gc_PreMarkCallback)(Ring2_Gc*, void*);

/// Add a premark callback to the GC.
/// Returns the Ring2_Gc_PreMarkCallbackId on success, `Ring2_Gc_PreMarkCallbackId_Invalid` on failure.
Ring2_Gc_PreMarkCallbackId
Ring2_Gc_addPreMarkCallback
  (
    Ring2_Gc* gc,
    void* object,
    Ring2_Gc_PreMarkCallback* callback
  );

/// Remove a "premark" callback from the GC.
/// This function silently ignores if `id` is Ring2_Gc_PreMarkCallbackId_Invalid.
void
Ring2_Gc_removePreMarkCallback
  (
    Ring2_Gc* gc,
    Ring2_Gc_PreMarkCallbackId id
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// `#define Ring2_Gc_SweepCallbackId_Invalid /*Implementation*/`
/// Symbolic constant of the invalid sweep callback ID.
/// Evaluates to `false` in boolean expressions.
#define Ring2_Gc_SweepCallbackId_Invalid ((uintptr_t)0)

/// `typedef /*Implementation*/ Ring2_Gc_SweepCallbackId`
/// Transparent type of a sweep callbackroot ID.
typedef uintptr_t Ring2_Gc_SweepCallbackId;

/// Type of a "sweep" callback.
typedef void (Ring2_Gc_SweepCallback)(Ring2_Gc*, void*, Ring2_Gc_SweepStatistics*);

/// Add a sweep callback to the GC.
/// Returns the Ring2_Gc_SweepCallbackId on success, `Ring2_Gc_SweepCallbackId_Invalid` on failure.
Ring2_Gc_SweepCallbackId
Ring2_Gc_addSweepCallback
  (
    Ring2_Gc* gc,
    void* object,
    Ring2_Gc_SweepCallback* callback
  );


/// Remove a "sweep" callback from the GC.
/// This function silently ignores if `id` is Ring2_Gc_SweepCallbackId_Invalid.
void
Ring2_Gc_removeSweepCallback
  (
    Ring2_Gc* gc,
    Ring2_Gc_SweepCallbackId id
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// ```
/// Ring2_Gc *
/// Ring2_Gc_create
///   (
///   );
/// ```
/// Create the GC.
/// Returns a pointer to a GC on success, returns a null pointer on failure.
Ring2_Gc *
Ring2_Gc_create
  (
  );

/// ```
/// void
/// Ring2_Gc_destroy
///  (
///    Ring2_Gc *gc
///  )
/// ```
/// Destroy the GC.
/// Undefined behavior if `gc` does not refer to a GC previously created by a call to `Ring2_Gc_create`.
void
Ring2_Gc_destroy
  (
    Ring2_Gc *gc
  );

void*
Ring2_Gc_allocate
  (
    Ring2_Gc* gc,
    size_t size,
    Ring2_Gc_Type const *type,
    Ring2_Gc_Tag** objectList
  );

Ring2_Gc_Tag*
Ring2_Gc_toTag
  (
    void* x
  );

void*
Ring2_Gc_toAddress
  (
    Ring2_Gc_Tag* x
  );

void
Ring2_Gc_visit
  (
    Ring2_Gc* gc,
    void *address
  );

void
Ring2_Gc_run
  (
    Ring2_Gc* gc,
    Ring2_Gc_RunStatistics *statistics
  );

#endif // RING2_GC_H_INCLUDED
