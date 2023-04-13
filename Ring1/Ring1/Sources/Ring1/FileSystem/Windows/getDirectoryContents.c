// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/FileSystem/Windows/getDirectoryContents.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/FileSystem/Windows/getDirectoryContents.h"

#include "Ring1/Status.h"
#include "Ring1/FileSystem/Windows/FileHandle.h"
#include "Ring1/FileSystem/Windows/FileMemoryMapping.h"
#include <stdio.h>

Ring1_NoDiscardReturn() Ring1_Result
Ring1_FileSystem_Windows_getDirectoryContents
  (
    Ring1_FileSystem_Path* path,
    Ring1_PointerList *contents
  )
{
  if (Ring1_Unlikely(!path)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  
  if (Ring1_Unlikely(!contents)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  return Ring1_Result_Success;
}
