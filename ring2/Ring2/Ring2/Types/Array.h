// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Array.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_ARRAY_H_INCLUDED)
#define RING2_TYPES_ARRAY_H_INCLUDED

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

#include "Ring2/Context.h"
#include "Ring2/Gc.h"
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

typedef struct Ring2_String Ring2_String;

/// @brief The C-level representation of an <code>Array</code> value.
typedef struct Ring2_Array Ring2_Array;
  
/*SWEEP*/ void
Ring2_ArrayModule_sweep
  (
    Ring2_Gc* gc,
    void* context,
    Ring2_Gc_SweepStatistics* statistics
  );

Ring1_CheckReturn() Ring1_Result
Ring2_ArrayModule_startup
  (
  );

void
Ring2_ArrayModule_shutdown
  (
  );

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
