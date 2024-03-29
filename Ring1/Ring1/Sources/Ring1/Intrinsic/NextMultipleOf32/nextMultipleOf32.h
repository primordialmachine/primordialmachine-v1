// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/NextMultipleOf32/nextMultipleOf32.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_NEXTMULTIPLEOF32_NEXTMULTIPLEOF32_H_INCLUDED)
#define RING1_INTRINSIC_NEXTMULTIPLEOF32_NEXTMULTIPLEOF32_H_INCLUDED

#include <inttypes.h>
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf32_u8
  (
    uint8_t *result,
    uint8_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf32_u16
  (
    uint16_t *result,
    uint16_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf32_u32
  (
    uint32_t *result,
    uint32_t x
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf32_u64
  (
    uint64_t *result,
    uint64_t x
  );
  
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf32_sz
  (
    size_t *result,
    size_t x
  );

#endif // RING1_INTRINSIC_NEXTMULTIPLEOF32_NEXTMULTIPLEOF32_H_INCLUDED
