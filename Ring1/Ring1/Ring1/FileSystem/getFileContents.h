// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_GETFILECONTENTS_H_INCLUDED)
#define RING1_FILESYSTEM_GETFILECONTENTS_H_INCLUDED

#include "Ring1/FileSystem/MemoryCallbacks.h"
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <stddef.h>


// https://documentation.primordialmachine.com/ring1-library/filesystem-library/Ring1_FileSystem_getFileContents
Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_getFileContents
  (
    char const* pathname,
    Ring1_FileSystem_AllocateCallback* allocate,
    Ring1_FileSystem_DeallocateCallback* deallocate,
    char** bytes,
    size_t* numberOfBytes
  );

#endif // RING1_FILESYSTEM_GETFILECONTENTS_H_INCLUDED
