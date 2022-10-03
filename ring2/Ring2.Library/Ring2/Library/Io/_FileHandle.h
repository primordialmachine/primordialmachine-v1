// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/_FileHandle.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_IO__FILEHANDLE_H_INCLUDED)
#define RING2_LIBRARY_IO__FILEHANDLE_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Io/_FileHandle.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"
#include "Ring2/Library/Io/_FileHandle.h"
#include "Ring1/FileSystem.h"
#include "Ring1/Status.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/// @brief Helper for file handles.
typedef struct _Machine_FileHandle {
  HANDLE hHandle;
} _Machine_FileHandle;

void
_Machine_FileHandle_open
  (
    _Machine_FileHandle* self, Ring2_String* path,
    Ring1_FileSystem_FileAccessMode fileAccessMode,
    Ring1_FileSystem_ExistingFilePolicy existingFilePolicy,
    Ring1_FileSystem_NonExistingFilePolicy nonExistingFilePolicy
  );

void
_Machine_FileHandle_close
  (
    _Machine_FileHandle* self
  );

size_t
_Machine_FileHandle_getFileSize
  (
    _Machine_FileHandle* self
  );

#endif // RING2_LIBRARY_IO__FILEHANDLE_H_INCLUDED
