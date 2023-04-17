// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/getTemporaryDirectory.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_GETTEMPORARYDIRECTORY_H_INCLUDED)
#define RING1_FILESYSTEM_GETTEMPORARYDIRECTORY_H_INCLUDED

#include "Ring1/FileSystem/Path.h"
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"

// https://primordialmachine.com/api/ring1-library/filesystem-library/Ring1_FileSystem_getTemporaryDirectory
Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_getTemporaryDirectory
  (
    Ring1_FileSystem_Path **result
  );

#endif // RING1_FILESYSTEM_GETTEMPORARYDIRECTORY_H_INCLUDED
