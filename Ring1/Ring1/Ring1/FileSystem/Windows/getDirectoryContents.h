// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/getDirectoryContents.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_WINDOWS_GETDIRECTORYCONTENTS_H_INCLUDED)
#define RING1_FILESYSTEM_WINDOWS_GETDIRECTORYCONTENTS_H_INCLUDED

#include "Ring1/FileSystem/Configuration.h"
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) &&                         \
  RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS ==                            \
    RING1_FILESYSTEM_CONFIGURATION_BACKEND

#include "Ring1/Collections/_Include.h"
#include "Ring1/FileSystem/MemoryCallbacks.h"
typedef struct Ring1_FileSystem_Path Ring1_FileSystem_Path;

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_getDirectoryContents
  (
    Ring1_FileSystem_Path* path,
    Ring1_PointerList *contents
  );

#endif // RING1_FILESYSTEM_CONFIGURATION_BACKEND

#endif // RING1_FILESYSTEM_WINDOWS_GETDIRECTORYCONTENTS_H_INCLUDED
