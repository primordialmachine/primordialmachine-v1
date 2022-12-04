// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/FileHandle.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_WINDOWS_FILEMEMORYMAPPING_H_INCLUDED)
#define RING1_FILESYSTEM_WINDOWS_FILEMEMORYMAPPING_H_INCLUDED

#include "Ring1/FileSystem/Configuration.h"
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) &&                         \
  RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS ==                            \
    RING1_FILESYSTEM_CONFIGURATION_BACKEND

#include "Ring1/FileSystem/Windows/FileHandle.h"

typedef struct Ring1_FileSystem_Windows_FileMemoryMapping {
  Ring1_FileSystem_Windows_FileHandle* fileHandle;
  HANDLE hFileMapping;
  char* bytes;
  size_t numberOfBytes;
} Ring1_FileSystem_Windows_FileMemoryMapping; // struct Ring1_FileSystem_Windows_FileMemoryMapping

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Windows_FileMemoryMapping_openRead
  (
    Ring1_FileSystem_Windows_FileMemoryMapping* self,
    const char* path
  );

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Windows_FileMemoryMapping_openWrite
  (
    Ring1_FileSystem_Windows_FileMemoryMapping* self,
    const char* path,
    size_t numberOfBytes
  );

void
Ring1_FileSystem_Windows_FileMemoryMapping_close
  (
    Ring1_FileSystem_Windows_FileMemoryMapping* self
  );

#endif // RING1_FILESYSTEM_CONFIGURATION_BACKEND

#endif // RING1_FILESYSTEM_WINDOWS_FILEMEMORYMAPPING_H_INCLUDED
