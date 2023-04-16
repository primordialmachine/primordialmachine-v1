#include <stdlib.h>
#include "Ring1/Object/Test/WeakReferenceTests.h"


int
Mkx_MathTest_run
  (
  )
{
  Ring1_Test_Context* ctx = NULL;

  if (Ring1_Test_Context_create(&ctx))
  {
    return 1;
  }
  if (Mkx_Object_Test_WeakReferenceTests_register(ctx))
  {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return 1;
  }
  if (Ring1_Test_Context_runAllTests(ctx))
  {
    Ring1_Test_Context_destroy(ctx);
    ctx = NULL;
    return 1;
  }
  Ring1_Test_Context_destroy(ctx);
  ctx = NULL;
  return 0;
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (Mkx_MathTest_run()) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
