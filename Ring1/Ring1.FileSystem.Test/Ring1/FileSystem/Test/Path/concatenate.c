#include "Ring1/FileSystem/TesT/Path/concatenate.h"
#include "Ring1/FileSystem/Test/Path/_validateResult.h"

static Ring1_NoDiscardReturn() Ring1_Result
testConcatenatePaths1
  (
    Ring1_Test_Context* ctx
  )
{
  Ring1_FileSystem_Path* prefix = NULL,
                       * suffix = NULL,
                       * path = NULL;

  if (Ring1_FileSystem_Path_create(&prefix, "C:/Programs", crt_strlen("C:/Programs"))) {
    return Ring1_Result_Failure;
  }
  if (Ring1_FileSystem_Path_create(&suffix, "Primordial Machine", crt_strlen("Primordial Machine"))) {
    Ring1_FileSystem_Path_unref(prefix);
    prefix = NULL;

    return Ring1_Result_Failure;
  }
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

  if (_validateResult(ctx, path, "C:/Programs/Primordial Machine")) {
    Ring1_FileSystem_Path_unref(path);
    path = NULL;

    return Ring1_Result_Failure;
  }
  
  Ring1_FileSystem_Path_unref(path);
  path = NULL;

  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Test_registerConcatenatePathTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.FileSystem.PathTest.concatenatePaths1", &testConcatenatePaths1)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}