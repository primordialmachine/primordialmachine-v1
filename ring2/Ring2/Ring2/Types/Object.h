// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Object.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_OBJECT_H_INCLUDED)
#define RING2_TYPES_OBJECT_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types/Object.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"
#include "Ring2/Gc.h"

Ring1_CheckReturn() Ring1_Result
Ring2_ObjectModule_startup
  (
  );

void
Ring2_ObjectModule_shutdown
  (
  );

/// @brief Allocate a GC object.
/// @param arguments A pointer to a Machine_Gc_AllocationArguments structure providing the arguments for the allocation.
/// @return A pointer to the object on success, a null pointer on failure.
void *
Ring2_ObjectModule_allocate
  (
    Ring2_Gc *gc,
    size_t size,
    Ring2_Gc_Type const *type
  );

#endif // Ring2_Configuration_withVoid

#endif // RING2_TYPES_VOID_H_INCLUDED
