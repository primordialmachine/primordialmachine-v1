/// @file Runtime/Io/_FileHandle.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO__FILEHANDLE_H_INCLUDED)
#define MACHINE_RUNTIME_IO__FILEHANDLE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/Io/FileHandle.h` directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/Assertions.h"
#include "Runtime/Io/_FileHandle.h"
#include "Ring2/_Include.h"
#include "Ring1/FileSystem.h"
#include "Runtime/LogModule.h"
#include "Ring1/Status.h"
#include "Runtime/String.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/// @brief Helper for file handles.
typedef struct _Machine_FileHandle {
  HANDLE hHandle;
} _Machine_FileHandle;

void _Machine_FileHandle_open(_Machine_FileHandle* self, Ring2_String* path,
                              Ring1_FileSystem_FileAccessMode fileAccessMode,
                              Ring1_FileSystem_ExistingFilePolicy existingFilePolicy,
                              Ring1_FileSystem_NonExistingFilePolicy nonExistingFilePolicy);

void _Machine_FileHandle_close(_Machine_FileHandle* self);

size_t _Machine_FileHandle_getFileSize(_Machine_FileHandle* self);

#endif // MACHINE_RUNTIME_IO__FILEHANDLE_H_INCLUDED
