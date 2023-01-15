// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/ApNatTests.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/ApNatTests.h"


#include "Ring1/Ap/Test/Nat/Add.h"
#include "Ring1/Ap/Test/Nat/Compare.h"
#include "Ring1/Ap/Test/Nat/Convert.h"
#include "Ring1/Ap/Test/Nat/Subtract.h"
#include "Ring1/Ap/Test/Nat/Multiply.h"
#include "Ring1/Ap/_Include.h"
#include "Ring1/Status.h"
#include <stdio.h>

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Ap_Test_registerApNatTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Ap_Test_Nat_registerAddTests(ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Ap_Test_Nat_registerCompareTests(ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Ap_Test_Nat_registerConvertTests(ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Ap_Test_Nat_registerSubtractTests(ctx)) {
     return Ring1_Result_Failure;
  }
  if (Ring1_Ap_Test_Nat_registerMultiplyTests(ctx)) {
     return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
