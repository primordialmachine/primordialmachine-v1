// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Libc/getFileContents.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_LIBC_GETFILECONTENTS_H_INCLUDED)
#define RING1_FILESYSTEM_LIBC_GETFILECONTENTS_H_INCLUDED

#include "Ring1/FileSystem.h"

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_receiveFileContents
  (
    const char* pathname,
    void* context,
    Ring1_FileSystem_ReceiveCallback* receive
  );

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_getFileContents
  (
    const char* pathname,
    Ring1_FileSystem_AllocateCallback* allocate,
    Ring1_FileSystem_DeallocateCallback* deallocate,
    char** bytes,
    size_t* numberOfBytes
  );

#endif // RING1_FILESYSTEM_LIBC_GETFILECONTENTS_H_INCLUDED
