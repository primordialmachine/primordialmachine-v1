// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Winapi/getFileContents.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Winapi/getFileContents.h"

#include "Ring1/Status.h"
#include "Ring1/FileSystem/Winapi/FileHandle.h"
#include "Ring1/FileSystem/Winapi/FileMemoryMapping.h"
#include <stdio.h>

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Winapi_receiveFileContents
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

  Ring1_FileSystem_Winapi_FileMemoryMapping memoryMapping;
  if (Ring1_FileSystem_Winapi_FileMemoryMapping_openRead(&memoryMapping, pathname)) {
    fprintf(stderr, "unable to open file '%s' for reading\n", pathname);
    return Ring1_Result_Failure;
  }

  if ((*receive)(context, memoryMapping.bytes, memoryMapping.numberOfBytes)) {
    fprintf(stderr, "unable to receive %zu Bytes\n", memoryMapping.numberOfBytes);
    Ring1_FileSystem_Winapi_FileMemoryMapping_close(&memoryMapping);
    return Ring1_Result_Failure;   
  }

  Ring1_FileSystem_Winapi_FileMemoryMapping_close(&memoryMapping);
  
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Winapi_getFileContents
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
  Ring1_FileSystem_Winapi_FileMemoryMapping memoryMapping;
  if (Ring1_FileSystem_Winapi_FileMemoryMapping_openRead(&memoryMapping, pathname)) {
    fprintf(stderr, "unable to open file '%s' for reading\n", pathname);
    return Ring1_Result_Failure;
  }

  void* p = NULL;
  size_t n = memoryMapping.numberOfBytes;
  if (allocate(&p, n)) {
    fprintf(stderr, "unable to allocate %zu Bytes\n", n);
    Ring1_FileSystem_Winapi_FileMemoryMapping_close(&memoryMapping);
    return Ring1_Result_Failure;
  }
  memcpy(p, memoryMapping.bytes, memoryMapping.numberOfBytes);
  *bytes = p;
  *numberOfBytes = n;

  Ring1_FileSystem_Winapi_FileMemoryMapping_close(&memoryMapping);

  return Ring1_Result_Success;
}
