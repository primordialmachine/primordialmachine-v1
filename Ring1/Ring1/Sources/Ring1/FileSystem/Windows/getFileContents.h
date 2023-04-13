// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/getFileContents.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_WINDOWS_GETFILECONTENTS_H_INCLUDED)
#define RING1_FILESYSTEM_WINDOWS_GETFILECONTENTS_H_INCLUDED

#include "Ring1/FileSystem/Configuration.h"
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) &&                         \
  RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS ==                            \
    RING1_FILESYSTEM_CONFIGURATION_BACKEND

#include "Ring1/FileSystem/MemoryCallbacks.h"
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_getFileContents
  (
    const char* pathname,
    Ring1_FileSystem_AllocateCallback* allocate,
    Ring1_FileSystem_DeallocateCallback* deallocate,
    char** bytes,
    size_t* numberOfBytes
  );

#endif // RING1_FILESYSTEM_CONFIGURATION_BACKEND

#endif // RING1_FILESYSTEM_WINDOWS_GETFILECONTENTS_H_INCLUDED
