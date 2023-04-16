#include <stdlib.h>

#include "Mkx/Scribe/Test/Cas/CasAdjugateTests.h"
#include "Mkx/Scribe/Test/Cas/CasCofactorMatrixTests.h"
#include "Mkx/Scribe/Test/Cas/CasConstantFoldingTests.h"
#include "Mkx/Scribe/Test/Cas/CasDeleteColumnTests.h"
#include "Mkx/Scribe/Test/Cas/CasDeleteRowTests.h"
#include "Mkx/Scribe/Test/Cas/CasDeterminantTests.h"
#include "Mkx/Scribe/Test/Cas/CasMatrixAdditionTests.h"
#include "Mkx/Scribe/Test/Cas/CasMatrixMultiplicationTests.h"
#include "Mkx/Scribe/Test/Cas/CasMatrixSubtractionTests.h"
#include "Mkx/Scribe/Test/Cas/CasTests.h"
#include "Mkx/Scribe/Test/Cas/CasTransposeTests.h"

Ring1_Result
Mkx_MediaTest_run
  (
  )
{
  Ring1_Test_Context* ctx = NULL;
  if (Ring1_Test_Context_create(&ctx)) {
    return Ring1_Result_Failure;
  }
  if (Mkx_Scribe_Cas_Test_registerAdjugateTests(ctx) ||
      Mkx_Scribe_Cas_Test_registerCofactorMatrixTests(ctx) ||
      Mkx_Scribe_Cas_Test_registerConstantFoldingTests(ctx) ||
      Mkx_Scribe_Cas_Test_registerCasTests(ctx) ||
      Mkx_Scribe_Cas_Test_registerDeleteColumnTests(ctx) ||
      Mkx_Scribe_Cas_Test_registerDeleteRowTests(ctx) ||
      Mkx_Scribe_Cas_Test_registerDeterminantTests(ctx) ||
      Mkx_Scribe_Cas_Test_registerMatrixAdditionTests(ctx) ||
      Mkx_Scribe_Cas_Test_registerMatrixMultiplicationTests(ctx) ||
      Mkx_Scribe_Cas_Test_registerMatrixSubtractionTests(ctx) ||
      Mkx_Scribe_Cas_Test_registerTransposeTests(ctx)) {
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
    int argc,
    char** argv
  )
{
  if (Mkx_MediaTest_run())
  { return EXIT_FAILURE; }
  return EXIT_SUCCESS;
}
