// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/setRegularContents.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Windows/setRegularContents.h"

#include "Ring1/Status.h"
#include "Ring1/FileSystem/Windows/FileHandle.h"
#include "Ring1/FileSystem/Windows/FileMemoryMapping.h"
#include <stdio.h>

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_setRegularContents
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
  Ring1_FileSystem_Windows_FileMemoryMapping memoryMapping;
  if (Ring1_FileSystem_Windows_FileMemoryMapping_openWrite(&memoryMapping, pathname, numberOfBytes)) {
    fprintf(stderr, "unable to open file '%s' for writing\n", pathname);
    return Ring1_Result_Failure;
  }
  memcpy(memoryMapping.bytes, bytes, numberOfBytes);
  Ring1_FileSystem_Windows_FileMemoryMapping_close(&memoryMapping);
  return Ring1_Result_Success;
}
