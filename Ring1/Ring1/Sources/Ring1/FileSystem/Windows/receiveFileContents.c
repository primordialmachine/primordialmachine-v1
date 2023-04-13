// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/receiveFileContents.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Windows/receiveFileContents.h"

#include "Ring1/Status.h"
#include "Ring1/FileSystem/Windows/FileHandle.h"
#include "Ring1/FileSystem/Windows/FileMemoryMapping.h"
#include <stdio.h>

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_receiveFileContents
  (
    const char* pathname,
    void *context,
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

  Ring1_FileSystem_Windows_FileMemoryMapping memoryMapping;
  if (Ring1_FileSystem_Windows_FileMemoryMapping_openRead(&memoryMapping, pathname)) {
    fprintf(stderr, "unable to open file '%s' for reading\n", pathname);
    return Ring1_Result_Failure;
  }

  if ((*receive)(context, memoryMapping.bytes, memoryMapping.numberOfBytes)) {
    fprintf(stderr, "unable to receive %zu Bytes\n", memoryMapping.numberOfBytes);
    Ring1_FileSystem_Windows_FileMemoryMapping_close(&memoryMapping);
    return Ring1_Result_Failure;   
  }

  Ring1_FileSystem_Windows_FileMemoryMapping_close(&memoryMapping);
  
  return Ring1_Result_Success;
}
