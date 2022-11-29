// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Libc/FileHandle.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_LIBC_FILEHANDLE_H_INCLUDED)
#define RING1_FILESYSTEM_LIBC_FILEHANDLE_H_INCLUDED

#include <stdio.h>
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

/// @brief C standard library implementation of a Ring1_FileSystem_FileHandle.
typedef struct Ring1_FileSystem_Libc_FileHandle
{
  FILE *fileDescriptor;
} Ring1_FileSystem_Libc_FileHandle;

// file must exist
Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_FileHandle_createRead
  (
    Ring1_FileSystem_Libc_FileHandle **result,
    const char *pathname
  );

// if existst, truncate existing. if not exists, create new.
Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_FileHandle_createWrite
  (
    Ring1_FileSystem_Libc_FileHandle** result,
    const char* pathname
  );

Ring1_CheckReturn() Ring1_Result
  Ring1_FileSystem_Libc_FileHandle_createStandardOutput
  (
    Ring1_FileSystem_Libc_FileHandle** result
  );

Ring1_CheckReturn() Ring1_Result
  Ring1_FileSystem_Libc_FileHandle_createStandardError
  (
    Ring1_FileSystem_Libc_FileHandle** result
  );

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_FileHandle_createStandardInput
  (
    Ring1_FileSystem_Libc_FileHandle** result
  );

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_FileHandle_getFileSize
  (
    size_t *result,
    Ring1_FileSystem_Libc_FileHandle *self
  );

void
Ring1_FileSystem_Libc_FileHandle_destroy
  (
    Ring1_FileSystem_Libc_FileHandle *self
  );

#endif // RING1_FILESYSTEM_LIBC_FILEHANDLE_H_INCLUDED
