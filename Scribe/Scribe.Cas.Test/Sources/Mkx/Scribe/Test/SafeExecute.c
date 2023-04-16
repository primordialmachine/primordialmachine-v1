#include "Mkx/Scribe/Test/SafeExecute.h"

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Test_safeExecute
  (
    void (*function)()
  )
{
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment))
  {
    (*function)();
    Ring2_popJumpTarget();
    return Ring1_Result_Success;
  }
  else
  {
    Ring2_popJumpTarget();
    return Ring1_Result_Failure;
  }
}
