// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/receiveRegularContents.h
/// @copyright Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_FILESYSTEM_RECEIVEREGULARCONTENTS_INCLUDE_H_INCLUDED)
#define RING1_FILESYSTEM_RECEIVEREGULARCONTENTS_INCLUDE_H_INCLUDED

#include "Ring1/FileSystem/Path.h"
#include "Ring1/FileSystem/ReceiveCallback.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_receiveRegularContents
  (
    Ring1_FileSystem_Path *path,
    void* context,
    Ring1_FileSystem_ReceiveCallback* receive
  );

#endif // RING1_FILESYSTEM_RECEIVEREGULARCONTENTS_INCLUDE_H_INCLUDED
