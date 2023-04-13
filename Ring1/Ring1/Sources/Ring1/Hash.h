// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Hash.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_HASH_H_INCLUDED)
#define RING1_HASH_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <inttypes.h>
#include <stdbool.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_p
  (
    size_t* result,
    void const* value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_p
  (
    int64_t* result,
    void const* value
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_b
  (
    size_t* result,
    bool value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_b
  (
    int64_t* result,
    bool value
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_i64
  (
    int64_t* result,
    int64_t value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_i64
  (
    size_t* result,
    int64_t value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_i32
  (
    int64_t* result,
    int32_t value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_i32
  (
    size_t* result,
    int32_t value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_i16
  (
    int64_t* result,
    int16_t value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_i16
  (
    size_t* result,
    int16_t value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_i8
  (
    int64_t* result,
    int8_t value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_i8
  (
    size_t* result,
    int8_t value
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_u64
  (
    size_t* result,
    uint64_t value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_u32
  (
    size_t* result,
    uint32_t value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_u16
  (
    size_t* result,
    uint16_t value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_u8
  (
    size_t* result,
    uint8_t value
  );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_f32
  (
    size_t* result,
    float value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_f32
  (
    int64_t* result,
    float value
  );


Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_f64
  (
    size_t* result,
    double value
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_f64
  (
    int64_t* result,
    double value
  );

#endif // RING1_HASH_H_INCLUDED
