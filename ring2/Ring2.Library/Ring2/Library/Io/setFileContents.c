// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/setFileContents.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Io/setFileContents.h"


#include "Ring1/FileSystem.h"
#include "Ring2/Library/Io/Initialize.h"


void
Machine_setFileContentsByteBuffer
  (
    Ring2_String* path,
    Ring2_ByteBuffer* byteBuffer
  )
{
  Machine_Io_initialize();
  path = Machine_Io_makePathname(Ring2_Context_get(), path);
  if (Ring1_FileSystem_setFileContents(Ring2_String_getBytes(path),
                                       Ring2_ByteBuffer_getBytes(byteBuffer),
                                       Ring2_ByteBuffer_getNumberOfBytes(byteBuffer))) {
    Ring2_jump();
  }
}

void
Machine_setFileContentsString
  (
    Ring2_String* path,
    Ring2_String* string
  )
{
  Machine_Io_initialize();
  path = Machine_Io_makePathname(Ring2_Context_get(), path);
  if (Ring1_FileSystem_setFileContents(Ring2_String_getBytes(path),
                                       Ring2_String_getBytes(string),
                                       Ring2_String_getNumberOfBytes(string))) {
    Ring2_jump();
  }
}
