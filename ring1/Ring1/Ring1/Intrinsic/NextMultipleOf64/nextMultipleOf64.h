// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/NextMultipleOf64/nextMultipleOf64.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_NEXTMULTIPLEOF64_NEXTMULTIPLEOF64_H_INCLUDED)
#define RING1_INTRINSIC_NEXTMULTIPLEOF64_NEXTMULTIPLEOF64_H_INCLUDED

#include <inttypes.h>
#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf64_u8
  (
    uint8_t *result,
    uint8_t x
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf64_u16
  (
    uint16_t *result,
    uint16_t x
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf64_u32
  (
    uint32_t *result,
    uint32_t x
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf64_u64
  (
    uint64_t *result,
    uint64_t x
  );


Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf64_sz
  (
    size_t *result,
    size_t x
  );

#endif // RING1_INTRINSIC_NEXTMULTIPLEOF64_NEXTMULTIPLEOF64_H_INCLUDED
