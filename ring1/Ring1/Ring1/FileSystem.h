// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_H_INCLUDED)
#define RING1_FILESYSTEM_H_INCLUDED

#include "Ring1/FileSystem/ExistingFilePolicy.h"
#include "Ring1/FileSystem/FileAccessMode.h"
#include "Ring1/FileSystem/NonExistingFilePolicy.h"
#include "Ring1/Annotations/_Include.h"
#include "Ring1/Module.h"
#include "Ring1/Result.h"

Ring1_Module_Declare(FileSystem)

// Callback invoked when n Bytes pointed to by p should be appended to an opaque context.
typedef Ring1_Result(Ring1_FileSystem_ReceiveCallback)(void* context, void* p, size_t n);

// https://documentation.primordialmachine.com/ring1-library/filesystem-library/Ring1_FileSystem_AllocateCallback
typedef Ring1_Result(Ring1_FileSystem_AllocateCallback)(void** p, size_t n);

// https://documentation.primordialmachine.com/ring1-library/filesystem-library/Ring1_FileSystem_DeallocateCallback
typedef Ring1_Result(Ring1_FileSystem_DeallocateCallback)(void* p);

Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_receiveFileContents
  (
    const char* pathname,
    void* context,
    Ring1_FileSystem_ReceiveCallback* receive
  );

// https://documentation.primordialmachine.com/ring1-library/filesystem-library/Ring1_FileSystem_getFileContents
Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_getFileContents
  (
    char const* pathname,
    Ring1_FileSystem_AllocateCallback* allocate,
    Ring1_FileSystem_DeallocateCallback* deallocate,
    char** bytes,
    size_t* numberOfBytes
  );

// https://documentation.primordialmachine.com/ring1-library/filesystem-library/Ring1_FileSystem_setFileContents
Ring1_CheckReturn() Ring1_Result
Ring1_FileSystem_setFileContents
  (
    char const* pathname,
    void const* bytes,
    size_t numberOfBytes
  );

#endif // RING1_FILESYSTEM_H_INCLUDED
