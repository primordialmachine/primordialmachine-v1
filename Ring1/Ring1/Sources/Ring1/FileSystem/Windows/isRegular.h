// Copyright (c) 2023 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/isRegular.h
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_WINDOWS_ISREGULAR_H_INCLUDED)
#define RING1_FILESYSTEM_WINDOWS_ISREGULAR_H_INCLUDED

#include "Ring1/FileSystem/Configuration.h"
#if defined(RING1_FILESYSTEM_CONFIGURATION_BACKEND) &&                         \
  RING1_FILESYSTEM_CONFIGURATION_BACKEND_WINDOWS ==                            \
    RING1_FILESYSTEM_CONFIGURATION_BACKEND

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <stdbool.h>

/// @error #Ring1_Status_InvalidArgument @a result is a null pointer
/// @error #Ring1_Status_InvalidArgument @a path is a null pointer
/// @error #Ring1_Status_AllocationFailed an allocation faileed
Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_isRegular
  (
    bool* result,
    char const* path
  );

#endif // RING1_FILESYSTEM_CONFIGURATION_BACKEND

#endif // RING1_FILESYSTEM_WINDOWS_ISREGULAR_H_INCLUDED
