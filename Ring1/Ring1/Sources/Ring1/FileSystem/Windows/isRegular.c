// Copyright (c) 2023 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/isRegular.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Windows/isRegular.h"

#include "Ring1/FileSystem/Path.h"
#include "Ring1/Status.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


Ring1_NoDiscardReturn() Ring1_Result
isFile
  (
    bool* result,
    Ring1_FileSystem_Path* path
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(!path)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  char* bytes; size_t numberOfBytes;
  if (Ring1_FileSystem_Path_toString(path, true, &bytes, &numberOfBytes)) {
    return Ring1_Result_Failure;
  }
  DWORD t = GetFileAttributesA(bytes);
  if (t == INVALID_FILE_ATTRIBUTES) {
    // error or not found
    *result = false;
    return Ring1_Result_Success;
  }
  if (FILE_ATTRIBUTE_NORMAL != t) {
    *result = false;
    return Ring1_Result_Success;
  }
  else {
    *result = true;
    return Ring1_Result_Success;
  }
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_isRegular
  (
    bool* result,
    char const* path
  )
{ 
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(!path)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path* path1;
  if (Ring1_FileSystem_Path_create(&path1, path, strlen(path))) {
    return Ring1_Result_Failure;
  }
  if (isRegular(result, path1)) {
    Ring1_FileSystem_Path_unref(path1);
    path = NULL;
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Path_unref(path1);
  path = NULL;
  return Ring1_Result_Success;
}
