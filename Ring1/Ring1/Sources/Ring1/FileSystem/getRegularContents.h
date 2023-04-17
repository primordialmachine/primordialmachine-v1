// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/getRegularContents.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_GETREGULARCONTENTS_H_INCLUDED)
#define RING1_FILESYSTEM_GETREGULARECONTENTS_H_INCLUDED


#include "Ring1/FileSystem/MemoryCallbacks.h"
#include "Ring1/FileSystem/Path.h"
#include "Ring1/Result.h"


// https://primordialmachine.com/api/ring1-library/filesystem-library/Ring1_FileSystem_getRegularContents
Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_getRegularContents
  (
    Ring1_FileSystem_Path* path,
    Ring1_FileSystem_AllocateCallback* allocate,
    Ring1_FileSystem_DeallocateCallback* deallocate,
    char** bytes,
    size_t* numberOfBytes
  );


#endif // RING1_FILESYSTEM_GETREGULARCONTENTS_H_INCLUDED
