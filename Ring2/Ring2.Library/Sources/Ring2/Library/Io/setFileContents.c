// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/setFileContents.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Io/setFileContents.h"


#include "Ring1/FileSystem/_Include.h"
#include "Ring2/Library/Io/Initialize.h"


void
Machine_setFileContentsByteBuffer
  (
    Ring2_String* path,
    Ring2_ByteBuffer* byteBuffer
  )
{
  Machine_Io_initialize();
  Ring1_FileSystem_Path* path1;
  if (Ring1_FileSystem_Path_create(&path1, Ring2_String_getBytes(path), (size_t)Ring2_String_getNumberOfBytes(path))) {
    Ring2_jump();
  }
  if (Ring1_FileSystem_setFileContents(path1,
                                       Ring2_ByteBuffer_getBytes(byteBuffer),
                                       (size_t)Ring2_ByteBuffer_getNumberOfBytes(byteBuffer))) {
    Ring1_FileSystem_Path_unref(path1);
    path1 = NULL;
    Ring2_jump();
  } else {
    Ring1_FileSystem_Path_unref(path1);
    path1 = NULL;
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
  Ring1_FileSystem_Path* path1;
  if (Ring1_FileSystem_Path_create(&path1, Ring2_String_getBytes(path), Ring2_String_getNumberOfBytes(path))) {
    Ring2_jump();
  }
  if (Ring1_FileSystem_setFileContents(path1,
                                       Ring2_String_getBytes(string),
                                       (size_t)Ring2_String_getNumberOfBytes(string))) {
    Ring1_FileSystem_Path_unref(path1);
    path1 = NULL;
    Ring2_jump();
  } else {
    Ring1_FileSystem_Path_unref(path1);
    path1 = NULL;
  }
}
