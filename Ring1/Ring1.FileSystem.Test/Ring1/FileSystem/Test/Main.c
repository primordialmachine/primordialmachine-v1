// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Test/Main.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include <stdlib.h>
#include "Ring1/FileSystem/Test/Path.h"
#include "Ring1/Test.h"
#include "Ring1/All/_Include.h"

// If defined to @a 1, then path tests are excluded.
#define ExcludePathTests (0)

// If defined to @a 1, then get current directory tests are excluded.
#define ExcludeGetCurrentDirectoryTests (1)

static Ring1_NoDiscardReturn() Ring1_Result
testCurrentDirectory1
  (
    Ring1_Test_Context* ctx
  )
{
  Ring1_FileSystem_Path* path;
  if (Ring1_FileSystem_getCurrentDirectory(&path)) {
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path_unref(path);
  path = NULL;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Test_registerCurrrentDirectoryTests
  (
    Ring1_Test_Context* ctx
  )
{ 
#if !defined(ExcludePathTests) || 1 != ExcludePathTests
  if (Ring1_FileSystem_Test_registerPathTests(ctx)) {
    return Ring1_Result_Failure;
  }
#endif
#if !defined(ExcludeGetCurrentDirectoryTests) || 1 != ExcludeGetCurrentDirectoryTests
  if (Ring1_FileSystem_Test_registerGetCurrentDirectoryTests(ctx)) {
    return Ring1_Result_Failure;
  }
#endif
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Test_run
  (
  )
{
  Ring1_Test_Context* ctx = NULL;
  if (Ring1_Test_Context_create(&ctx)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_FileSystem_Test_registerCurrrentDirectoryTests(ctx)) {
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
