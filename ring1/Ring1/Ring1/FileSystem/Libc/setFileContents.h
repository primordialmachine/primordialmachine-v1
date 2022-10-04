// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Libc/setFileContents.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_LIBC_SETFILECONTENTS_H_INCLUDED)
#define RING1_FILESYSTEM_LIBC_SETFILECONTENTS_H_INCLUDED

#include "Ring1/FileSystem.h"

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_Libc_setFileContents
  (
    const char* pathname,
    const char* bytes,
    size_t numberOfBytes
  );

#endif // RING1_FILESYSTEM_LIBC_SETFILECONTENTS_H_INCLUDED
