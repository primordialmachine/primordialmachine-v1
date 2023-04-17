// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Test/Main.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include <stdlib.h>
#include "Ring1/FileSystem/Test/getCurrentDirectory.h"
#include "Ring1/FileSystem/Test/getTemporaryDirectory.h"
#include "Ring1/FileSystem/Test/Path.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Test_run
  (
  )
{
  Ring1_Test_Context* ctx = NULL;
  if (Ring1_Test_Context_create(&ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_FileSystem_Test_registerGetCurrentDirectoryTests(ctx) ||
      Ring1_FileSystem_Test_registerGetTemporaryDirectoryTests(ctx) ||
      Ring1_FileSystem_Test_registerPathTests(ctx)) {
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
  )
{
  Ring1_All_ModuleHandle handle;
  handle = Ring1_All_ModuleHandle_acquire();
  if (!handle) {
    return Ring1_Result_Failure;
  }
  if (Ring1_FileSystem_Test_run()) {
    Ring1_All_ModuleHandle_relinquish(handle);
    handle = Ring1_All_ModuleHandle_Invalid;
    return EXIT_FAILURE;
  }
  Ring1_All_ModuleHandle_relinquish(handle);
  handle = Ring1_All_ModuleHandle_Invalid;
  return EXIT_SUCCESS;
}
