// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem.h"

#include "Ring1/FileSystem/Configuration.h"
#include <stdio.h>

#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Libc/getFileContents.h"
  #include "Ring1/FileSystem/Libc/setFileContents.h"
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  #include "Ring1/FileSystem/Winapi/getFileContents.h"
  #include "Ring1/FileSystem/Winapi/setFileContents.h"
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI")
#endif

#include "Ring1/Memory.h"

static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_Module_Define(FileSystem, initializeModule, uninitializeModule)

static Ring1_Memory_ModuleHandle g_memoryModuleHandle =
    Ring1_Memory_ModuleHandle_Invalid;

static Ring1_Result
initializeModule
  (
  )
{
  g_memoryModuleHandle = Ring1_Memory_ModuleHandle_acquire();
  if (!g_memoryModuleHandle) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
uninitializeModule
  (
  )
{
  Ring1_Memory_ModuleHandle_relinquish(g_memoryModuleHandle);
  g_memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_receiveFileContents
  (
    const char* pathname,
    void* context,
    Ring1_FileSystem_ReceiveCallback* receive
  )
{
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Libc_receiveFileContents(pathname, context, receive);
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Winapi_receiveFileContents(pathname, context, receive);
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI")
#endif
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_getFileContents
  (
    char const* pathname,
    Ring1_FileSystem_AllocateCallback* allocate,
    Ring1_FileSystem_DeallocateCallback* deallocate,
    char** bytes,
    size_t* numberOfBytes
  )
{ 
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Libc_getFileContents(pathname, allocate, deallocate, bytes, numberOfBytes);
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Winapi_getFileContents(pathname, allocate, deallocate, bytes, numberOfBytes);
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI")
#endif
}

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_setFileContents
  (
    char const* pathname,
    void const* bytes,
    size_t numberOfBytes
  )
{
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Libc_setFileContents(pathname, bytes, numberOfBytes);
#elif defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) && RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI == RING1_FILESYSTEM_CONFIGURATION_BACKEND
  return Ring1_FileSystem_Winapi_setFileContents(pathname, bytes, numberOfBytes);
#else
  #error("RING1_FILESYSTEM_CONFIGURATION_BACKEND must be defined to RING1_FILESYSTEM_CONFIGURATION_BACKEND_LIBC or RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINAPI")
#endif
}
