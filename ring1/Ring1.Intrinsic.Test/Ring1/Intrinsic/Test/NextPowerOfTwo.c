// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/NextPowerOfTwo.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/NextPowerOfTwo.h"

#include "Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo.h"
#include <inttypes.h>
#include "Ring1/Status.h"

void
Mkx_Intrinsic_Test_nextPowerOfTwo_s8
  (
    Ring1_Test_Context* ctx
  )
{
  int8_t x, y;
  Ring1_Result r;

  // Special case of x = 0.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 0;
  r = Ring1_Intrinsic_nextPowerOfTwo_s8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Special case of x = 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_s8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Normal case x = 2.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 2;
  r = Ring1_Intrinsic_nextPowerOfTwo_s8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 2);

  // Normal case x = 3.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 3;
  r = Ring1_Intrinsic_nextPowerOfTwo_s8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 4);

  // Normal case x = INTn_MAX - 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = INT8_MAX - 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_s8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = INTn_MAX.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = INT8_MAX;
  r = Ring1_Intrinsic_nextPowerOfTwo_s8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = 16.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 16;
  r = Ring1_Intrinsic_nextPowerOfTwo_s8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 16);
}

void
Mkx_Intrinsic_Test_nextPowerOfTwo_u8
  (
    Ring1_Test_Context* ctx
  )
{
  uint8_t x, y;
  Ring1_Result r;

  // Special case of x = 0.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 0;
  r = Ring1_Intrinsic_nextPowerOfTwo_u8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Special case of x = 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_u8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Normal case x = 2.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 2;
  r = Ring1_Intrinsic_nextPowerOfTwo_u8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 2);

  // Normal case x = 3.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 3;
  r = Ring1_Intrinsic_nextPowerOfTwo_u8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 4);

  // Normal case x = 128.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 128;
  r = Ring1_Intrinsic_nextPowerOfTwo_u8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 128);

  // Normal case x = UINTn_MAX - 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = UINT8_MAX - 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_u8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = UINTn_MAX.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = UINT8_MAX;
  r = Ring1_Intrinsic_nextPowerOfTwo_u8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = 16.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 16;
  r = Ring1_Intrinsic_nextPowerOfTwo_u8(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 16);
}

void
Mkx_Intrinsic_Test_nextPowerOfTwo_s16
  (
    Ring1_Test_Context* ctx
  )
{
  int16_t x, y;
  Ring1_Result r;

  // Special case of x = 0.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 0;
  r = Ring1_Intrinsic_nextPowerOfTwo_s16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Special case of x = 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_s16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Normal case x = 2.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 2;
  r = Ring1_Intrinsic_nextPowerOfTwo_s16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 2);

  // Normal case x = 3.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 3;
  r = Ring1_Intrinsic_nextPowerOfTwo_s16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 4);

  // Normal case x = INTn_MAX - 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = INT16_MAX - 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_s16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = INTn_MAX.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = INT16_MAX;
  r = Ring1_Intrinsic_nextPowerOfTwo_s16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = 16.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 16;
  r = Ring1_Intrinsic_nextPowerOfTwo_s16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 16);
}

void
Mkx_Intrinsic_Test_nextPowerOfTwo_u16
  (
    Ring1_Test_Context* ctx
  )
{
  uint16_t x, y;
  Ring1_Result r;

  // Special case of x = 0.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 0;
  r = Ring1_Intrinsic_nextPowerOfTwo_u16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Special case of x = 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_u16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Normal case x = 2.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 2;
  r = Ring1_Intrinsic_nextPowerOfTwo_u16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 2);

  // Normal case x = 3.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 3;
  r = Ring1_Intrinsic_nextPowerOfTwo_u16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 4);

  // Normal case x = 128.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 128;
  r = Ring1_Intrinsic_nextPowerOfTwo_u16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 128);

  // Normal case x = UINTn_MAX - 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = UINT16_MAX - 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_u16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = UINTn_MAX.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = UINT16_MAX;
  r = Ring1_Intrinsic_nextPowerOfTwo_u16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = 16.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 16;
  r = Ring1_Intrinsic_nextPowerOfTwo_u16(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 16);
}

void
Mkx_Intrinsic_Test_nextPowerOfTwo_s32
  (
    Ring1_Test_Context* ctx
  )
{
  int32_t x, y;
  Ring1_Result r;

  // Special case of x = 0.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 0;
  r = Ring1_Intrinsic_nextPowerOfTwo_s32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Special case of x = 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_s32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Normal case x = 2.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 2;
  r = Ring1_Intrinsic_nextPowerOfTwo_s32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 2);

  // Normal case x = 3.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 3;
  r = Ring1_Intrinsic_nextPowerOfTwo_s32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 4);

  // Normal case x = INTn_MAX - 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = INT32_MAX - 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_s32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = INTn_MAX.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = INT32_MAX;
  r = Ring1_Intrinsic_nextPowerOfTwo_s32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = 16.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 16;
  r = Ring1_Intrinsic_nextPowerOfTwo_s32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 16);
}

void
Mkx_Intrinsic_Test_nextPowerOfTwo_u32
  (
    Ring1_Test_Context* ctx
  )
{
  uint32_t x, y;
  Ring1_Result r;

  // Special case of x = 0.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 0;
  r = Ring1_Intrinsic_nextPowerOfTwo_u32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Special case of x = 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_u32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Normal case x = 2.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 2;
  r = Ring1_Intrinsic_nextPowerOfTwo_u32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 2);

  // Normal case x = 3.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 3;
  r = Ring1_Intrinsic_nextPowerOfTwo_u32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 4);

  // Normal case x = 128.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 128;
  r = Ring1_Intrinsic_nextPowerOfTwo_u32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 128);

  // Normal case x = UINTn_MAX - 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = UINT32_MAX - 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_u32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = UINTn_MAX.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = UINT32_MAX;
  r = Ring1_Intrinsic_nextPowerOfTwo_u32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = 16.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 16;
  r = Ring1_Intrinsic_nextPowerOfTwo_u32(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, y, 16);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
}

void
Mkx_Intrinsic_Test_nextPowerOfTwo_s64
  (
    Ring1_Test_Context* ctx
  )
{
  int64_t x, y;
  Ring1_Result r;

  // Special case of x = 0.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 0;
  r = Ring1_Intrinsic_nextPowerOfTwo_s64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Special case of x = 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_s64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Normal case x = 2.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 2;
  r = Ring1_Intrinsic_nextPowerOfTwo_s64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 2);

  // Normal case x = 3.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 3;
  r = Ring1_Intrinsic_nextPowerOfTwo_s64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 4);

  // Normal case x = INTn_MAX - 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = INT64_MAX - 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_s64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = INTn_MAX.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = INT64_MAX;
  r = Ring1_Intrinsic_nextPowerOfTwo_s64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = 16.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 16;
  r = Ring1_Intrinsic_nextPowerOfTwo_s64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 16);
}

void
Mkx_Intrinsic_Test_nextPowerOfTwo_u64
  (
    Ring1_Test_Context* ctx
  )
{
  uint64_t x, y;
  Ring1_Result r;

  // Special case of x = 0.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 0;
  r = Ring1_Intrinsic_nextPowerOfTwo_u64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Special case of x = 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_u64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Normal case x = 2.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 2;
  r = Ring1_Intrinsic_nextPowerOfTwo_u64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 2);

  // Normal case x = 3.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 3;
  r = Ring1_Intrinsic_nextPowerOfTwo_u64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 4);

  // Normal case x = 128.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 128;
  r = Ring1_Intrinsic_nextPowerOfTwo_u64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 128);

  // Normal case x = UINTn_MAX - 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = UINT64_MAX - 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_u64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = UINTn_MAX.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = UINT64_MAX;
  r = Ring1_Intrinsic_nextPowerOfTwo_u64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = 16.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 16;
  r = Ring1_Intrinsic_nextPowerOfTwo_u64(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 16);
}

void
Mkx_Intrinsic_Test_nextPowerOfTwo_sz
  (
    Ring1_Test_Context* ctx
  )
{
  size_t x, y;
  Ring1_Result r;

  // Special case of x = 0.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 0;
  r = Ring1_Intrinsic_nextPowerOfTwo_sz(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Special case of x = 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_sz(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 1);

  // Normal case x = 2.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 2;
  r = Ring1_Intrinsic_nextPowerOfTwo_sz(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 2);

  // Normal case x = 3.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 3;
  r = Ring1_Intrinsic_nextPowerOfTwo_sz(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 4);

  // Normal case x = 128.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 128;
  r = Ring1_Intrinsic_nextPowerOfTwo_sz(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 128);

  // Normal case x = SIZE_MAX - 1.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = SIZE_MAX - 1;
  r = Ring1_Intrinsic_nextPowerOfTwo_sz(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = SIZE_MAX.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = SIZE_MAX;
  r = Ring1_Intrinsic_nextPowerOfTwo_sz(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  Ring1_Status_set(Ring1_Status_Success);

  // Special case x = 16.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  x = 16;
  r = Ring1_Intrinsic_nextPowerOfTwo_sz(&y, x);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 16);
}

Ring1_Result
Ring1_Intrinsic_Test_registerNextPowerOfTwoTests
  (
    Ring1_Test_Context* ctx
  )
{
  return
     Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.nextPowerOfTwo[u8]",
                                &Mkx_Intrinsic_Test_nextPowerOfTwo_u8)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.nextPowerOfTwo[s8]",
                                &Mkx_Intrinsic_Test_nextPowerOfTwo_s8)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.nextPowerOfTwo[u16]",
                                &Mkx_Intrinsic_Test_nextPowerOfTwo_u16)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.nextPowerOfTwo[s16]",
                                &Mkx_Intrinsic_Test_nextPowerOfTwo_s16)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.nextPowerOfTwo[u32]",
                                &Mkx_Intrinsic_Test_nextPowerOfTwo_u32)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.nextPowerOfTwo[s32]",
                                &Mkx_Intrinsic_Test_nextPowerOfTwo_s32)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.nextPowerOfTwo[u64]",
                                &Mkx_Intrinsic_Test_nextPowerOfTwo_u64)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.nextPowerOfTwo[s64]",
                                &Mkx_Intrinsic_Test_nextPowerOfTwo_s64)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.nextPowerOfTwo[sz]",
                                &Mkx_Intrinsic_Test_nextPowerOfTwo_sz)
  ;
}
