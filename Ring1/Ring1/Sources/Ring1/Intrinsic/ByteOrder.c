// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/ByteOrder.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/ByteOrder.h"


static Ring1_NoDiscardReturn() Ring1_Result
Ring1_reorderBytes
  (
    char const* source,
    char* target,
    size_t n
  )
{
  for (size_t i = 0, m = n / 2; i < m; ++i) {
    char temporary = target[i];
    target[i] = target[n - i - 1];
    target[n - i - 1] = temporary;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_s16
  (
    int16_t* result,
    int16_t self
  )
{
  uint16_t result1, self1;
  self1 = (uint16_t)self;
  if (Ring1_swapEndian_u16(&result1, self1)) {
    return Ring1_Result_Failure;
  }
  *result = (int16_t)result1;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_u16
  (
    uint16_t* result,
    uint16_t self
  )
{
  (*result) = (self & 0xff00) >> 8 |
              (self & 0x00ff) << 8;

  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_s32
  (
    int32_t* result,
    int32_t self
  )
{
  uint32_t result1, self1;
  self1 = (uint32_t)self;
  if (Ring1_swapEndian_u32(&result1, self1)) {
    return Ring1_Result_Failure;
  }
  *result = (int32_t)result1;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_u32
  (
    uint32_t* result,
    uint32_t self
  )
{
  *result = (self & 0xff000000) >> 24 |
            (self & 0x00ff0000) >>  8 |
            (self & 0x0000ff00) <<  8 |
            (self & 0x000000ff) << 24;

  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_s64
  (
    int64_t* result,
    int64_t self
  )
{
  return Ring1_reorderBytes((char const*)&self, (char*)result, 4);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_swapEndian_u64
  (
    uint64_t* result,
    uint64_t self
  )
{ return Ring1_reorderBytes((char const*)&self, (char*)result, 8); }
