/// @file Runtime/Gc/Gc.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_GC_GC_H_INCLUDED)
#define MACHINE_RUNTIME_GC_GC_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/Gc/Gc.h` directly, include `_Runtime.h` instead.")
#endif
#include "Ring2/_Include.h"
#include "Ring1/Result.h"

/// @brief Arguments for a call to Machine_Gc_allocate.
typedef struct Machine_Gc_AllocationArguments {

  /// @brief The size, in Bytes, of the suffix.
  size_t suffixSize;

  Ring2_Gc_Type const* type;

} Machine_Gc_AllocationArguments;

Ring1_CheckReturn() Ring1_Result
Machine_Gc_startup();

void
Machine_Gc_shutdown();

/// @brief Allocate a GC object.
/// @param arguments A pointer to a Machine_Gc_AllocationArguments structure providing the arguments for the allocation.
/// @return A pointer to the object on success, a null pointer on failure.
void* Machine_Gc_allocate(Machine_Gc_AllocationArguments const* arguments);

/// @brief Visit an object.
/// @param object A pointer to the object.
/// @undefined Invoked outside of visit callback.
void Machine_Gc_visit(void* object);

void Machine_Gc_preMarkCallback(Ring2_Gc* gc, void* context);

void Machine_Gc_sweepCallback(Ring2_Gc* gc, void* context, Ring2_Gc_SweepStatistics *statistics);

/// @brief Run the GC.
/// @param statistics A pointer to a Mkx_Gc_RunStatistics object or a null pointer.
/// @param dead Pointer to a variable receiving the number of dead objects or a null pointer.
/// @success If @a runStatistics is not null, then the fields were assigned the statistics of this run.
void Machine_Gc_run(Ring2_Gc_RunStatistics *statistics);

#endif // MACHINE_RUNTIME_GC_GC_H_INCLUDED
