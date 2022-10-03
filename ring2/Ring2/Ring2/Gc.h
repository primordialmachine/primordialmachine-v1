// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Gc.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_GC_H_INCLUDED)
#define RING2_GC_H_INCLUDED


#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Gc.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"
#include "Ring2/Gc/Type.h"
#include "Ring2/Gc/Tag.h"
#include "Ring2/Gc/RunStatistics.h"
#include "Ring2/Gc/SweepStatistics.h"
#include <stdint.h>

/// The maximal size, in Bytes, of a memory block as an int64_t value.
#define Ring2_Gc_MaximumAllocatableSize \
  ((int64_t)(((SIZE_MAX < INT64_MAX) ? SIZE_MAX : INT64_MAX)- sizeof(Ring2_Gc_Tag)))

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

Ring1_CheckReturn() Ring2_Gc*
Ring2_Gc_get
  (
  );

/// @brief Startup the GC module.
/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
/// @remark This function sets the by-thread status variable on failure.
Ring1_CheckReturn() Ring1_Result
Ring2_Gc_startup
  (
  );

/// @brief Shutdown the GC module.
void
Ring2_Gc_shutdown
  (
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

/// @brief Increment the lock count of an object.
/// @param o A pointer to the object.
/*Ring1_Convenience()*/ Ring1_Inline() void
Ring2_Gc_lock
  (
    void* o
  )
{
  Ring2_Gc_Tag* t = Ring2_Gc_toTag(o);
  Ring2_Gc_Tag_lock(t);
}

/// @brief Decrement the lock count of an object.
/// @param o A pointer to the object.
/*Ring1_Convenience()*/ Ring1_Inline() void
Ring2_Gc_unlock
  (
    void* o
  )
{
  Ring2_Gc_Tag* t = Ring2_Gc_toTag(o);
  Ring2_Gc_Tag_unlock(t);
}

#endif // RING2_GC_H_INCLUDED
