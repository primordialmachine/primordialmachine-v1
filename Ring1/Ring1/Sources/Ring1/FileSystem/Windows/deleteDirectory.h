// Copyright (c) 2023 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/deleteDirectory.h
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_WINDOWS_DELETEDIRECTORY_H_INCLUDED)
#define RING1_FILESYSTEM_WINDOWS_DELETEDIRECTORY_H_INCLUDED

#include "Ring1/FileSystem/Configuration.h"
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) &&                         \
  RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS ==                            \
    RING1_FILESYSTEM_CONFIGURATION_BACKEND

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
typedef struct Ring1_FileSystem_Path Ring1_FileSystem_Path;

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Windows_deleteDirectory
  (
    Ring1_FileSystem_Path* path
  );

#endif // RING1_FILESYSTEM_CONFIGURATION_BACKEND

#endif // RING1_FILESYSTEM_WINDOWS_DELETEDIRECTORY_H_INCLUDED
