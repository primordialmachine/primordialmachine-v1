#include "Mkx/Scribe/Test/Cas/SafeExecute.h"

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_safeExecute
  (
    void (*function)()
  )
{
  return Mkx_Scribe_Test_safeExecute(function);
}
