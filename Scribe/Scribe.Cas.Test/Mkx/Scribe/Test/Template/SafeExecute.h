#pragma once


#include "Mkx/Scribe/Cas.h"
#include "Mkx/Scribe/Test/SafeExecute.h"


Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Template_Test_safeExecute
  (
    Mkx_Interpreter_Context* context,
    void (*function)(Mkx_Interpreter_Context *)
  );
