// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/setFileContents.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_SETFILECONTENTS_H_INCLUDED)
#define RING1_FILESYSTEM_SETFILECONTENTS_H_INCLUDED

#include "Ring1/FileSystem/MemoryCallbacks.h"
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <stddef.h>

// https://documentation.primordialmachine.com/ring1-library/filesystem-library/Ring1_FileSystem_setFileContents
Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_setFileContents
  (
    char const* pathname,
    void const* bytes,
    size_t numberOfBytes
  );

#endif // RING1_FILESYSTEM_SETFILECONTENTS_H_INCLUDED
