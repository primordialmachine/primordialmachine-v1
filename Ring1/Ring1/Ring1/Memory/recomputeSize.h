// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Memory/recomputeSize.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_MEMORY_RECOMPUTESIZE_H_INCLUDED)
#define RING1_MEMORY_RECOMPUTESIZE_H_INCLUDED

#include "Ring1/Memory/Configuration.h"
#include "Ring1/Result.h"
#include "Ring1/Annotations/_Include.h"
#include <stdint.h>
#include <stdbool.h>

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_recomputeSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_recomputeSize_u8
  (
    uint8_t min,
    uint8_t max,
    uint8_t old,
    uint8_t additional,
    uint8_t *new,
    bool saturate
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_recomputeSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_recomputeSize_s8
  (
    int8_t min,
    int8_t max,
    int8_t old,
    int8_t additional,
    int8_t *new,
    bool saturate
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_recomputeSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_recomputeSize_u16
  (
    uint16_t min,
    uint16_t max,
    uint16_t old,
    uint16_t additional,
    uint16_t *new,
    bool saturate
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_recomputeSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_recomputeSize_s16
  (
    int16_t min,
    int16_t max,
    int16_t old,
    int16_t additional,
    int16_t *new,
    bool saturate
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_recomputeSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_recomputeSize_u32
  (
    uint32_t min,
    uint32_t max,
    uint32_t old,
    uint32_t additional,
    uint32_t *new,
    bool saturate
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_recomputeSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_recomputeSize_s32
  (
    int32_t min,
    int32_t max,
    int32_t old,
    int32_t additional,
    int32_t *new,
    bool saturate
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_recomputeSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_recomputeSize_u64
  (
    uint64_t min,
    uint64_t max,
    uint64_t old,
    uint64_t additional,
    uint64_t *new,
    bool saturate
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_recomputeSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_recomputeSize_s64
  (
    int64_t min,
    int64_t max,
    int64_t old,
    int64_t additional,
    int64_t *new,
    bool saturate
  );

// https://primordialmachine.com/api/ring1-library/memory-library/Ring1_Memory_recomputeSize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_Memory_recomputeSize_sz
  (
    size_t min,
    size_t max,
    size_t old,
    size_t additional,
    size_t *new,
    bool saturate
  );

#endif // RING1_MEMORY_RECOMPUTESIZE_H_INCLUDED
