// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Array.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_ARRAY_H_INCLUDED)
#define RING2_TYPES_ARRAY_H_INCLUDED


#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types/Array.h` directly, include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

#include "Ring2/Gc.h"

/// @brief The C-level representation of an <code>Array</code> value.
typedef struct Ring2_Array Ring2_Array;
  
/*SWEEP*/ void
Ring2_ArrayModule_sweep
  (
    Ring2_Gc* gc,
    void* context,
    Ring2_Gc_SweepStatistics* statistics
  );

Ring1_Module_Declare(Ring2, ArrayModule)

Ring1_CheckReturn() Ring2_Array*
Ring2_ArrayHeap_createArray
  (
    Ring2_Context* context,
    int64_t length
  );

Ring1_CheckReturn() Ring2_String*
Ring2_ArrayModule_toString
  (
    Ring2_Context* context,
    Ring2_Array* self
  );

#endif // Ring2_Configuration_withArray

#endif // RING2_TYPES_ARRAY_H_INCLUDED
