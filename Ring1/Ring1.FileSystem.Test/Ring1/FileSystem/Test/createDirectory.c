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
testCreateDirectory1
(
  Ring1_Test_Context* ctx
)
{
  Ring1_FileSystem_Path* prefix;
  if (Ring1_FileSystem_getCurrentDirectory(&prefix)) {
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path* suffix;
  if (Ring1_FileSystem_Path_create(&suffix, "xyz", crt_strlen("xyz"))) {
    Ring1_FileSystem_Path_unref(prefix);
    prefix = NULL;
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path* path;
  if (Ring1_FileSystem_Path_concatenate(&path, prefix, suffix)) {
    Ring1_FileSystem_Path_unref(suffix);
    suffix = NULL;
    Ring1_FileSystem_Path_unref(prefix);
    prefix = NULL;
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path_unref(suffix);
  suffix = NULL;
  Ring1_FileSystem_Path_unref(prefix);
  prefix = NULL;

  if (Ring1_FileSystem_createDirectory(path)) {
    Ring1_FileSystem_Path_unref(path);
    path = NULL;
    return Ring1_Result_Failure;
  }

  if (Ring1_FileSystem_deleteDirectory(path)) {
    Ring1_FileSystem_Path_unref(path);
    path = NULL;
    return Ring1_Result_Failure;
  }

  Ring1_FileSystem_Path_unref(path);
  path = NULL;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Test_registerCreateDirectoryTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.createDirectoryTest", &testCreateDirectory1)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
