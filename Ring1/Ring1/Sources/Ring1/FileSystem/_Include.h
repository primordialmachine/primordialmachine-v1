// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/_Include.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM__INCLUDE_H_INCLUDED)
#define RING1_FILESYSTEM__INCLUDE_H_INCLUDED

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Module.h"
#include "Ring1/FileSystem/ExistingFilePolicy.h"
#include "Ring1/FileSystem/FileAccessMode.h"
#include "Ring1/FileSystem/FileAttributes.h"
#include "Ring1/FileSystem/getCurrentDirectory.h"
#include "Ring1/FileSystem/getFileAttributes.h"
#include "Ring1/FileSystem/getTemporaryDirectory.h"
#include "Ring1/FileSystem/NonExistingFilePolicy.h"
#include "Ring1/FileSystem/MemoryCallbacks.h"
#include "Ring1/FileSystem/Path.h"
#include "Ring1/FileSystem/ReceiveCallback.h"
#include "Ring1/FileSystem/getRegularContents.h"
#include "Ring1/FileSystem/setRegularContents.h"

Ring1_Module_Declare(Ring1, FileSystem)

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_receiveRegularContents
  (
    Ring1_FileSystem_Path *path,
    void* context,
    Ring1_FileSystem_ReceiveCallback* receive
  );

#endif // RING1_FILESYSTEM__INCLUDE_H_INCLUDED
