// Copyright (c) 2023 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/isDirectory.h
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_GETCURRENTDIRECTORY_H_INCLUDED)
#define RING1_FILESYSTEM_GETCURRENTDIRECTORY_H_INCLUDED

#include "Ring1/Collections/_Include.h"
#include "Ring1/FileSystem/Path.h"

// https://primordialmachine.com/api/ring1-library/filesystem-library/Ring1_FileSystem_isDirectory
Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_isDirectory
  (
    bool* result,
    char const* path
  );

#endif // RING1_FILESYSTEM_GETCURRENTDIRECTORY_H_INCLUDED
