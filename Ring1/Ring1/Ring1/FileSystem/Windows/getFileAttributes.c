// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/getFileAttributes.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Windows/getFileAttributes.h"

#include "Ring1/Memory.h"
#include "Ring1/Status.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Windows_getFileAttributes
  (
    const char *pathname,
    Ring1_FileSystem_FileAttributes *attibutes
  )
{
  if (Ring1_Unlikely(!pathname)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(!attibutes)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  WIN32_FILE_ATTRIBUTE_DATA attributes;
  if (!GetFileAttributesExA(pathname, GetFileExInfoStandard, &attributes)) {
    Ring1_Status_set(Ring1_Status_FileNotFound);
    return Ring1_Result_Failure;
  }

  *attibutes = 0;
  if (attributes.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
    *attibutes |= Ring1_FileSystem_FileAttributes_Regular;
  } else if (attributes.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) {
    *attibutes |= Ring1_FileSystem_FileAttributes_Regular;
  } else if (attributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
    *attibutes |= Ring1_FileSystem_FileAttributes_Directory;
  } else {
    // Do not set any flags in case of an unknown/unsupported file type.
  }

  return Ring1_Result_Success;
}
