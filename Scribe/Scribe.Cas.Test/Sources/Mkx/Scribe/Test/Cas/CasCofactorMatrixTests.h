#pragma once

#include "Ring1/Test.h"

/// @brief Register cofactor matrix tests with the test context.
/// @param ctx The test context.
/// @return #Ring1_Result_Success on success, #Ring1_Result_Failure on failure.
Ring1_CheckReturn() Ring1_Result
Mkx_Scribe_Cas_Test_registerCofactorMatrixTests
  (
    Ring1_Test_Context* ctx
  );
