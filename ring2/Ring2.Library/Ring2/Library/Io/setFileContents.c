// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/setFileContents.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Io/setFileContents.h"


#include "Ring1/FileSystem.h"
#include "Ring2/Library/Io/Initialize.h"


void
Machine_setFileContents
  (
    Ring2_String* path,
    Machine_ByteBuffer* bytes
  )
{
  Machine_Io_initialize();
  path = Ring2_String_concatenate(Ring2_Context_get(), path, Ring2_String_create(Ring2_Context_get(), "", 1));
  if (Ring1_FileSystem_setFileContents(Ring2_String_getBytes(Ring2_Context_get(), path),
                                       Machine_ByteBuffer_getBytes(bytes),
                                       Machine_ByteBuffer_getNumberOfBytes(bytes))) {
    Ring2_jump();
  }
}
