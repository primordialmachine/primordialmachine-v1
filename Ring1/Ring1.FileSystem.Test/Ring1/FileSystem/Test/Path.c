// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Test/Path.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Test/Path.h"
#include <stdlib.h>
#include "Ring1/Test.h"
#include "Ring1/All/_Include.h"

// if defined to @a 1, then tests for the empty path are excluded.
#define ExcludeEmptyPathTests (0)

// If defined to @a 1, then tests for the dot path are excluded.
#define ExcludeDotPathTests (0)

// If defined to @a 1, then tests for the dot dot path are excluded.
#define ExcludeDotDotPathTests (0)

// If defined to @a 1, then the tests for the root path are excluded.
#define ExcludeRootPathTests (0)

static Ring1_NoDiscardReturn() Ring1_Result
doTest
  (
    Ring1_Test_Context* ctx,
    const char *inputBytes,
    const char *expectedBytes
  )
{
  size_t numberOfInputBytes = crt_strlen(inputBytes);
  size_t numberOfExpectedBytes = crt_strlen(expectedBytes);
  
  Ring1_FileSystem_Path* path;
  if (Ring1_FileSystem_Path_create(&path, inputBytes, numberOfInputBytes)) {
    return Ring1_Result_Failure;
  }

  int result;
  char* receivedBytes;
  size_t numberOfReceivedBytes;
  
  // not zero terminated
  if (Ring1_FileSystem_Path_toString(path, false, &receivedBytes, &numberOfReceivedBytes)) {
    Ring1_FileSystem_Path_unref(path);
    path = NULL;
    return Ring1_Result_Failure;
  }
  
  if (Ring1_Memory_compare(&result, expectedBytes, numberOfExpectedBytes, receivedBytes, numberOfReceivedBytes, Ring1_Memory_Compare_Lexicographic)) {
    Ring1_Memory_deallocate(receivedBytes);
    receivedBytes = NULL;
    
    Ring1_FileSystem_Path_unref(path);
    path = NULL;
  
    return Ring1_Result_Failure;
  }
  
  RING1_TEST_ASSERT_EQ(ctx, result, 0);
  
  Ring1_Memory_deallocate(receivedBytes);
  receivedBytes = NULL;

  // zero-terminated
  if (Ring1_FileSystem_Path_toString(path, true, &receivedBytes, &numberOfReceivedBytes)) {
    Ring1_FileSystem_Path_unref(path);
    path = NULL;
    return Ring1_Result_Failure;
  }

  if (numberOfReceivedBytes != numberOfExpectedBytes + 1) {
    Ring1_Memory_deallocate(receivedBytes);
    receivedBytes = NULL;
    Ring1_FileSystem_Path_unref(path);
    path = NULL;
    return Ring1_Result_Failure;
  }

  if (Ring1_Memory_compare(&result, expectedBytes, numberOfExpectedBytes, receivedBytes, numberOfReceivedBytes - 1, Ring1_Memory_Compare_Lexicographic)) {
    Ring1_Memory_deallocate(receivedBytes);
    receivedBytes = NULL;
    Ring1_FileSystem_Path_unref(path);
    path = NULL;
    return Ring1_Result_Failure;
  }
  if (receivedBytes[numberOfReceivedBytes - 1] != '\0') {
    Ring1_Memory_deallocate(receivedBytes);
    receivedBytes = NULL;
    Ring1_FileSystem_Path_unref(path);
    path = NULL;
    return Ring1_Result_Failure;
  }

  RING1_TEST_ASSERT_EQ(ctx, result, 0);
  
  Ring1_FileSystem_Path_unref(path);
  path = NULL;
  
  return Ring1_Result_Success;
}


static Ring1_NoDiscardReturn() Ring1_Result
testEmptyPath
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "", "");
}

static Ring1_NoDiscardReturn() Ring1_Result
testDotPath
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, ".", ".");
}

static Ring1_NoDiscardReturn() Ring1_Result
testDotDotPath1
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "..", "..");
}

static Ring1_NoDiscardReturn() Ring1_Result
testDotDotPath2
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "hello/../", ".");
}

static Ring1_NoDiscardReturn() Ring1_Result
testRootPath1
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "C:", "C:");
}

static Ring1_NoDiscardReturn() Ring1_Result
testRootPath2
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "C:\\Windows", "C:\\Windows");
}

static Ring1_NoDiscardReturn() Ring1_Result
regression1
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "README.txt", "README.txt");
}

static Ring1_NoDiscardReturn() Ring1_Result
regression2
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "primordialmachine-24x24.png", "primordialmachine-24x24.png");
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Test_registerPathTests
  (
    Ring1_Test_Context* ctx
  )
{
#if !defined(ExcludeEmptyPathTests) || 1 != ExcludeEmptyPathTests
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.EmptyPath", &testEmptyPath)) {
    return Ring1_Result_Failure;
  }
#endif
#if !defined(ExcludeDotPathTests) || 1 != ExcludeDotPathTests
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.DotPath", &testDotPath)) {
    return Ring1_Result_Failure;
  }
#endif
#if !defined(ExcludeDotDotPathTests) || 1 != ExcludeDotDotPathTests
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.DotDotPath1", &testDotDotPath1)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.DotDotPath2", &testDotDotPath2)) {
    return Ring1_Result_Failure;
  }
#endif
#if !defined(ExcludeRootPathTests) || 1 != ExcludeRootPathTests
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.RootPath1", &testRootPath1)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.RootPath2", &testRootPath2)) {
    return Ring1_Result_Failure;
  }
#endif
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.Regression1", &regression1)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.Regression2", &regression2)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
