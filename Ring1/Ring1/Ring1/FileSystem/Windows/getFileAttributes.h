// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/getFileAttributes.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_WINDOWS_GETFILEATTRIBUTES_H_INCLUDED)
#define RING1_FILESYSTEM_WINDOWS_GETFILEATTRIBUTES_H_INCLUDED

#include "Ring1/FileSystem/Configuration.h"
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) &&                         \
  RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS ==                            \
    RING1_FILESYSTEM_CONFIGURATION_BACKEND

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include "Ring1/FileSystem/FileAttributes.h"

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Windows_getFileAttributes
  (
    const char* path,
    Ring1_FileSystem_FileAttributes* attributes
  );

#endif // RING1_FILESYSTEM_CONFIGURATION_BACKEND

#endif // RING1_FILESYSTEM_WINDOWS_GETFILEATTRIBUTES_H_INCLUDED
