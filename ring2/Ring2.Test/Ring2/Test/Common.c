#include "Ring2/Test/Common.h"

int
Mkx_Test_execute
  (
    Ring2_ForeignProcedure *testFunction
  )
{
  if (!testFunction) {
    return 1;
  }
  // Startup the interpreter context.
  if (Ring2_Context_startup()) {
    return 1;
  }
  int status = 0;
  // Safe execute.
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment))
  {
    Ring2_Value result = Ring2_Value_StaticInitializerVoid();
    Ring2_Value arguments[] = { Ring2_Value_StaticInitializerVoid() };
    (*testFunction)(Ring2_Context_get(), &result, 0, &arguments[0]);
    Ring2_popJumpTarget();
  }
  else
  {
    Ring2_popJumpTarget();
    status = 1;
  }
  // Destroy the interpreter context.
  Ring2_Context_shutdown();
  // Return the status.
  return status;
}