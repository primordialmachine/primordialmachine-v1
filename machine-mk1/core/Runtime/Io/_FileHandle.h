/// @file Runtime/Io/_FileHandle.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_IO__FILEHANDLE_H_INCLUDED)
#define MACHINE_RUNTIME_IO__FILEHANDLE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/Assertions.h"
#include "Runtime/Io/_FileHandle.h"
#include "Runtime/Io/ExistingFilePolicy.h"
#include "Runtime/Io/FileAccessMode.h"
#include "Runtime/Io/NonExistingFilePolicy.h"
#include "Ring2/JumpTarget.h"
#include "Runtime/LogModule.h"
#include "Runtime/Status.h"
#include "Runtime/String.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/// @brief Helper for file handles.
typedef struct _Machine_FileHandle {
  HANDLE hHandle;
} _Machine_FileHandle;

void _Machine_FileHandle_open(_Machine_FileHandle* self, Machine_String* path,
                              Machine_FileAccessMode fileAccessMode,
                              Machine_ExistingFilePolicy existingFilePolicy,
                              Machine_NonExistingFilePolicy nonExistingFilePolicy);

void _Machine_FileHandle_close(_Machine_FileHandle* self);

size_t _Machine_FileHandle_getFileSize(_Machine_FileHandle* self);

#endif // MACHINE_RUNTIME_IO__FILEHANDLE_H_INCLUDED
