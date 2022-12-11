// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/FileHandle.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_WINDOWS_FILEHANDLE_H_INCLUDED)
#define RING1_FILESYSTEM_WINDOWS_FILEHANDLE_H_INCLUDED

#include "Ring1/FileSystem/Configuration.h"
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) &&                         \
  RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS ==                            \
    RING1_FILESYSTEM_CONFIGURATION_BACKEND

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include "Ring1/FileSystem/ExistingFilePolicy.h"
#include "Ring1/FileSystem/FileAccessMode.h"
#include "Ring1/FileSystem/NonExistingFilePolicy.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_startup
  (
  );

void
Ring1_FileSystem_Windows_shutdown
  (
  );

/// @brief Windows implementation of a Ring1_FileSystem_FileHandle.
typedef struct Ring1_FileSystem_Windows_FileHandle
{
  // Default is INVALID_HANDLE_VALUE.
  HANDLE hFileHandle;
} Ring1_FileSystem_Windows_FileHandle;

// file must exist
Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_FileHandle_create
  (
    Ring1_FileSystem_Windows_FileHandle **result,
    const char *pathname,
    Ring1_FileSystem_FileAccessMode fileAccessMode,
    Ring1_FileSystem_ExistingFilePolicy existingFilePolicy,
    Ring1_FileSystem_NonExistingFilePolicy nonExistingFilePolicy
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_FileHandle_createStandardOutput
  (
    Ring1_FileSystem_Windows_FileHandle** result
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_FileHandle_createStandardError
  (
    Ring1_FileSystem_Windows_FileHandle** result
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_FileHandle_createStandardInput
  (
    Ring1_FileSystem_Windows_FileHandle** result
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_FileHandle_getFileSize
  (
    size_t *result,
    Ring1_FileSystem_Windows_FileHandle *self
  );

void
Ring1_FileSystem_Windows_FileHandle_destroy
  (
    Ring1_FileSystem_Windows_FileHandle *self
  );

#endif // RING1_FILESYSTEM_CONFIGURATION_BACKEND

#endif // RING1_FILESYSTEM_WINDOWS_FILEHANDLE_H_INCLUDED
