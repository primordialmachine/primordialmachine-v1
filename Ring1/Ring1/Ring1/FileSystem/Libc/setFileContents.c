// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Libc/setFileContents.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Libc/setFileContents.h"

#include "Ring1/Status.h"
#include "Ring1/FileSystem/Libc/FileHandle.h"
#include <stdio.h>

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_setFileContents
  (
    const char* pathname,
    const char* bytes,
    size_t numberOfBytes
  )
{
  if (Ring1_Unlikely(!pathname)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(!bytes)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Libc_FileHandle* fh = NULL;
  if (Ring1_FileSystem_Libc_FileHandle_createWrite(&fh, pathname)) {
    fprintf(stderr, "unable to open file '%s' for writing\n", pathname);
    return Ring1_Result_Failure;
  }
  size_t numberOfElementsWritten = fwrite(bytes, numberOfBytes, 1, fh->fileDescriptor);
  size_t numberOfBytesWritten = numberOfBytes * numberOfElementsWritten;
  if (numberOfBytes != numberOfBytesWritten) {
    Ring1_FileSystem_Libc_FileHandle_destroy(fh);
    fh = NULL;
    fprintf(stderr, "error writing file '%s'\n", pathname);
    Ring1_Status_set(Ring1_Status_EnvironmentFailed);
    return Ring1_Result_Failure;
  }
  Ring1_FileSystem_Libc_FileHandle_destroy(fh);
  fh = NULL;
  return Ring1_Result_Success;
}
