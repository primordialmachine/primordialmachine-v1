#include "Ring1/FileSystem/TesT/Path/create.h"
#include "Ring1/FileSystem/Test/Path/_validateResult.h"

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
  Ring1_FileSystem_Path* path;
  if (Ring1_FileSystem_Path_create(&path, inputBytes, numberOfInputBytes)) {
    return Ring1_Result_Failure;
  }
  if (_validateResult(ctx, path, expectedBytes)) {
    Ring1_FileSystem_Path_unref(path);
    path = NULL;
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path_unref(path);
  path = NULL;
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
testCreateEmptyPath
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "", "");
}

static Ring1_NoDiscardReturn() Ring1_Result
testCreateDotPath
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, ".", ".");
}

static Ring1_NoDiscardReturn() Ring1_Result
testCreateDotDotPath1
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "..", "..");
}

static Ring1_NoDiscardReturn() Ring1_Result
testCreateDotDotPath2
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "hello/../", ".");
}

static Ring1_NoDiscardReturn() Ring1_Result
testCreateRootPath1
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "C:", "C:");
}

static Ring1_NoDiscardReturn() Ring1_Result
testCreateRootPath2
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "C:\\Windows", "C:\\Windows");
}

static Ring1_NoDiscardReturn() Ring1_Result
testCreateTrailingSlash1
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "C:\\Windows\\", "C:\\Windows");
}

static Ring1_NoDiscardReturn() Ring1_Result
testCreateTrailingSlash2
  (
    Ring1_Test_Context* ctx
  )
{
  return doTest(ctx, "C:\\Windows\\\\", "C:\\Windows");
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
Ring1_FileSystem_Test_registerCreatePathTests
  (
    Ring1_Test_Context* ctx
  )
{
#if !defined(ExcludeEmptyPathTests) || 1 != ExcludeEmptyPathTests
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.createEmptyPath", &testCreateEmptyPath)) {
    return Ring1_Result_Failure;
  }
#endif
#if !defined(ExcludeDotPathTests) || 1 != ExcludeDotPathTests
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.createDotPath", &testCreateDotPath)) {
    return Ring1_Result_Failure;
  }
#endif
#if !defined(ExcludeDotDotPathTests) || 1 != ExcludeDotDotPathTests
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.createDotDotPath1", &testCreateDotDotPath1)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.createDotDotPath2", &testCreateDotDotPath2)) {
    return Ring1_Result_Failure;
  }
#endif
#if !defined(ExcludeRootPathTests) || 1 != ExcludeRootPathTests
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.createRootPath1", &testCreateRootPath1)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.createRootPath2", &testCreateRootPath2)) {
    return Ring1_Result_Failure;
  }
#endif
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.creatTrailingSlash1", &testCreateTrailingSlash1)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.creatTrailingSlash2", &testCreateTrailingSlash2)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.createRegression1", &regression1)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.createRegression2", &regression2)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
