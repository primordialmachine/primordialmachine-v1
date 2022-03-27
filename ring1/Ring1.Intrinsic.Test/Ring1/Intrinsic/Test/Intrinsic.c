// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Intrinsic/Test/Intrinsic.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/Intrinsic.h"

#include <stddef.h>

#include "Ring1/Intrinsic/Test/Add.h"
#include "Ring1/Intrinsic/Test/CountLeadingZeroes.h"
#include "Ring1/Intrinsic/Test/IsPowerOfTwo.h"
#include "Ring1/Intrinsic/Test/Multiply.h"
#include "Ring1/Intrinsic/Test/NextMultipleOf32.h"
#include "Ring1/Intrinsic/Test/NextMultipleOf64.h"
#include "Ring1/Intrinsic/Test/NextPowerOfTwo.h"
#include "Ring1/Intrinsic/Test/Subtract.h"

Ring1_CheckReturn() Ring1_Result
Mkx_Intrinsic_Test_runAll
  (
  )
{
  Ring1_Test_Context* ctx = NULL;
  
  if (Ring1_Test_Context_create(&ctx))
  { return Ring1_Result_Failure; }

  if (Ring1_Intrinsic_Test_registerIsPowerOfTwoTests(ctx)
      || Ring1_Intrinsic_Test_registerMultiplyTests(ctx)
      || Ring1_Intrinsic_Test_registerAddTests(ctx)
      || Ring1_Intrinsic_Test_registerSubtractTests(ctx)
      || Ring1_Intrinsic_Test_registerNextPowerOfTwoTests(ctx)
      || Ring1_Intrinsic_Test_registerNextMultipleOf32Tests(ctx)
      || Ring1_Intrinsic_Test_registerNextMultipleOf64Tests(ctx)) {
    return Ring1_Result_Failure;
  }

  if (// Mkx_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[s8]", &Mkx_Intrinsic_Test_multiply_s8)
      //|| Mkx_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[u8]", &Mkx_Intrinsic_Test_multiply_u8)
      //
      //|| Mkx_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[s16]", &Mkx_Intrinsic_Test_multiply_s16)
      //|| Mkx_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[u16]", &Mkx_Intrinsic_Test_multiply_u16)
      //
      //|| Mkx_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[s32]", &Mkx_Intrinsic_Test_multiply_s32)
      //|| Mkx_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[u32]", &Mkx_Intrinsic_Test_multiply_u32)
      //
      //|| Mkx_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[s64]", &Mkx_Intrinsic_Test_multiply_s64)
      //|| Mkx_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[u64]", &Mkx_Intrinsic_Test_multiply_u64)
      //
       Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.countLeadingZeroes[u8]",
                                  &Mkx_Intrinsic_Test_countLeadingZeroes_u8)
    || Ring1_Test_Context_addTest(ctx, "Ring1.Intrinsic.Test.countLeadingZeroes[u16]",
                                  &Mkx_Intrinsic_Test_countLeadingZeroes_u16)
    || Ring1_Test_Context_addTest(ctx, "Ring1.Intrinsic.Test.countLeadingZeroes[u32]",
                                  &Mkx_Intrinsic_Test_countLeadingZeroes_u32)
    || Ring1_Test_Context_addTest(ctx, "Ring1.Intrinsic.Test.countLeadingZeroes[u64]",
                                  &Mkx_Intrinsic_Test_countLeadingZeroes_u64))
  {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_runAllTests(ctx))
  {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return Ring1_Result_Failure;
  }
  Ring1_Test_Context_destroy(ctx);
  ctx = NULL;
  return Ring1_Result_Success;
}
