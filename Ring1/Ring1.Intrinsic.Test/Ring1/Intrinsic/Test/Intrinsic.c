// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Intrinsic/Test/Intrinsic.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/Intrinsic.h"

#include <stddef.h>

#include "Ring1/Intrinsic/Test/Add.h"
#include "Ring1/Intrinsic/Test/Clamp.h"
#include "Ring1/Intrinsic/Test/CountLeadingZeroes.h"
#include "Ring1/Intrinsic/Test/IsPowerOfTwo.h"
#include "Ring1/Intrinsic/Test/Maximum.h"
#include "Ring1/Intrinsic/Test/Minimum.h"
#include "Ring1/Intrinsic/Test/Multiply.h"
#include "Ring1/Intrinsic/Test/NextMultipleOf32.h"
#include "Ring1/Intrinsic/Test/NextMultipleOf64.h"
#include "Ring1/Intrinsic/Test/NextPowerOfTwo.h"
#include "Ring1/Intrinsic/Test/Subtract.h"

Ring1_NoDiscardReturn() Ring1_Result
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
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return Ring1_Result_Failure;
  }

  if (Ring1_Intrinsic_Test_registerClampTests(ctx)) {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return Ring1_Result_Failure;
  }

  if (Ring1_Intrinsic_Test_registerMaximumTests(ctx)) {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return Ring1_Result_Failure;
  }

  if (Ring1_Intrinsic_Test_registerMinimumTests(ctx)) {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return Ring1_Result_Failure;
  }

  if (Ring1_Intrinsic_Test_registerCountLeadingZeroesTests(ctx)) {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_runAllTests(ctx)) {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return Ring1_Result_Failure;
  }
  Ring1_Test_Context_destroy(ctx);
  ctx = NULL;
  return Ring1_Result_Success;
}
