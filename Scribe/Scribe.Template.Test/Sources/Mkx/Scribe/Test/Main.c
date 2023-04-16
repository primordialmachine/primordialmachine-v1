#include <stdlib.h>

#include "Mkx/Scribe/Test/Template/TemplateTests.h"

Ring1_Result
Mkx_MediaTest_run
  (
  )
{
  Ring1_Test_Context* ctx = NULL;
  if (Ring1_Test_Context_create(&ctx)) {
    return Ring1_Result_Failure;
  }
  if (Mkx_Scribe_Template_Test_registerTemplateTests(ctx)) {
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
    int argc,
    char** argv
  )
{
  if (Mkx_MediaTest_run())
  { return EXIT_FAILURE; }
  return EXIT_SUCCESS;
}
