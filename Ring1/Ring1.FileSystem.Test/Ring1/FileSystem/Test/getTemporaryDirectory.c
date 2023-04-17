// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Test/getCurrentDirectory.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Test/getCurrentDirectory.h"

#include <stdlib.h>
#include "Ring1/FileSystem/Test/Path.h"
#include "Ring1/Test.h"
#include "Ring1/All/_Include.h"

static Ring1_NoDiscardReturn() Ring1_Result
testGetTemporaryDirectory1
  (
    Ring1_Test_Context* ctx
  )
{
  Ring1_FileSystem_Path* path;
  if (Ring1_FileSystem_getTemporaryDirectory(&path)) {
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path_unref(path);
  path = NULL;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Test_registerGetTemporaryDirectoryTests
  (
    Ring1_Test_Context* ctx
  )
{ 
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.getTemporaryDirectoryTest1", &testGetTemporaryDirectory1)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
