#include "Mkx/Scribe/Test/Template/SafeExecute.h"

Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Template_Test_safeExecute
  (
    Mkx_Interpreter_Context* context,
    void (*function)(Mkx_Interpreter_Context *)
  )
{
  return Mkx_Scribe_Test_safeExecute(context, function);
}
