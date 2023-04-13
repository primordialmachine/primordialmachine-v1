// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/ReferenceCounter.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/ReferenceCounter.h"

#include "Ring1/Intrinsic/atomicDecrement.h"
#include "Ring1/Intrinsic/atomicGet.h"
#include "Ring1/Intrinsic/atomicIncrement.h"

int32_t
Ring1_ReferenceCounter_get
  (
    Ring1_ReferenceCounter const* referenceCounter
  )
{ return Ring1_Intrinsic_atomicGet_s32(referenceCounter); }

int32_t
Ring1_ReferenceCounter_increment
  (
    Ring1_ReferenceCounter* referenceCounter
  )
{ return Ring1_Intrinsic_atomicIncrement_s32(referenceCounter); }

int32_t
Ring1_ReferenceCounter_decrement
  (
    Ring1_ReferenceCounter* referenceCounter
  )
{ return Ring1_Intrinsic_atomicDecrement_s32(referenceCounter); }
