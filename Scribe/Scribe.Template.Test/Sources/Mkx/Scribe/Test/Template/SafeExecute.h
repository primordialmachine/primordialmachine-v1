#pragma once

#include "Mkx/Scribe/Test/SafeExecute.h"


Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Template_Test_safeExecute
  (
    bool expectSuccess,
    void (*function)()
  );

void
Mkx_Scribe_Template_Test_execute
  (
    Ring2_Context* ctx,
    const char* configurationPathName,
    const char* sourcePathName,
    const char* targetPathName
  );
