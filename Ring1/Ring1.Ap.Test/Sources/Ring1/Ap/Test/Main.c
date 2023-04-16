// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/Main.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include <stdlib.h>
#include "Ring1/Ap/Test/ApBoolTests.h"
#include "Ring1/Ap/Test/ApIntTests.h"
#include "Ring1/Ap/Test/ApNatTests.h"
#include "Ring1/Ap/Test/ApRealTests.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Ap_Test_run
  (
  )
{
  Ring1_Test_Context* ctx = NULL;
  if (Ring1_Test_Context_create(&ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Ap_Test_registerApBoolTests(ctx) ||
      Ring1_Ap_Test_registerApIntTests(ctx) ||
      Ring1_Ap_Test_registerApNatTests(ctx) ||
      Ring1_Ap_Test_registerApRealTests(ctx)) {
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

int
main
  (
  )
{
  if (Ring1_Ap_Test_run()) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
