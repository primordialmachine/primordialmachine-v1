// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Libc/getFileContents.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Libc/getFileContents.h"

#include "Ring1/Status.h"
#include "Ring1/FileSystem/Libc/FileHandle.h"
#include <stdio.h>

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_receiveFileContents
  (
    const char* pathname,
    void* context,
    Ring1_FileSystem_ReceiveCallback* receive
  )
{
  if (Ring1_Unlikely(!pathname)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  
  if (Ring1_Unlikely(!receive)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  Ring1_FileSystem_Libc_FileHandle* fileHandle = NULL;
  if (Ring1_FileSystem_Libc_FileHandle_createRead(&fileHandle, pathname)) {
    fprintf(stderr, "unable to open file '%s' for reading\n", pathname);
    return Ring1_Result_Failure;
  }

  size_t bufferSize = 0;
  char buffer[512];
  while (1) {
    size_t bufferSize = fread(&buffer[0], 1, 512, fileHandle->fileDescriptor);
    if (512 != bufferSize) {
      if (ferror(fileHandle->fileDescriptor)) {
        fprintf(stderr, "error reading file '%s'\n", pathname);
        Ring1_Status_set(Ring1_Status_EnvironmentFailed);
        return Ring1_Result_Failure;
      }
      /*if (feof(fileHandle->fileDescriptor))*/ {
        if ((*receive)(context, buffer, bufferSize)) {
          return Ring1_Result_Failure;
        }
      }
    } else {
      if ((*receive)(context, buffer, bufferSize)) {
        return Ring1_Result_Failure;
      }
    }
  }

  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_getFileContents
  (
    const char* pathname,
    Ring1_FileSystem_AllocateCallback* allocate,
    Ring1_FileSystem_DeallocateCallback* deallocate,
    char** bytes,
    size_t* numberOfBytes
  )
{
  if (Ring1_Unlikely(!pathname)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  
  if (Ring1_Unlikely(!allocate || !deallocate)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  if (Ring1_Unlikely(!bytes || !numberOfBytes)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  //
  Ring1_FileSystem_Libc_FileHandle* fh = NULL;
  if (Ring1_FileSystem_Libc_FileHandle_createRead(&fh, pathname)) {
    fprintf(stderr, "unable to open file '%s' for reading\n", pathname);
    return Ring1_Result_Failure;
  }

  size_t n;
  if (Ring1_FileSystem_Libc_FileHandle_getFileSize(&n, fh)) {
    Ring1_FileSystem_Libc_FileHandle_destroy(fh);
    fh = NULL;
    fprintf(stderr, "unable to determine file size of file '%s\n", pathname);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }

  //
  char* p;
  if ((*allocate)(&p, n > 0 ? n : 1)) {
    Ring1_FileSystem_Libc_FileHandle_destroy(fh);
    fh = NULL;
    fprintf(stderr, "unable to allocate %zu Bytes\n", n);
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }

  //
  size_t m = fread(p, 1, n, fh->fileDescriptor);
  if (n != m) {
    (*deallocate)(p);
    p = NULL;
    Ring1_FileSystem_Libc_FileHandle_destroy(fh);
    fh = NULL;
    fprintf(stderr, "error reading file '%s'\n", pathname);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }

  //
  Ring1_FileSystem_Libc_FileHandle_destroy(fh);
  fh = NULL;

  //
  *bytes = p;
  *numberOfBytes = n;

  //
  return Ring1_Result_Success;
}
