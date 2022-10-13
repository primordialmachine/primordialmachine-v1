// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/getFileContents.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Io/getFileContents.h"


#include "Ring1/FileSystem.h"
#include "Ring1/Intrinsic.h"
#include "Ring2/Library/Io/Initialize.h"


static Ring1_Result
onReceiveByteBuffer
  (
    Ring2_ByteBuffer *self,
    const char *p,
    size_t n
  )
{
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring2_ByteBuffer_appendBytes(self, p, n);
    Ring2_popJumpTarget();
    return Ring1_Result_Success;
  } else {
    Ring2_popJumpTarget();
    return Ring1_Result_Failure;
  }
}

Ring2_ByteBuffer*
Machine_getFileContentsAsByteBuffer
  (
    Ring2_String* path
  )
{
  Machine_Io_initialize();
  path = Ring2_String_concatenate(Ring2_Context_get(), path, Ring2_String_create(Ring2_Context_get(), "", 1));
  Ring2_ByteBuffer* byteBuffer = Ring2_ByteBuffer_create();
  Machine_appendFileContents(path, byteBuffer);
  return byteBuffer;
}

void
Machine_appendFileContents
  (
    Ring2_String* path,
    Ring2_ByteBuffer* byteBuffer
  )
{
  Machine_Io_initialize();
  path = Ring2_String_concatenate(Ring2_Context_get(), path, Ring2_String_create(Ring2_Context_get(), "", 1));
  if (Ring1_FileSystem_receiveFileContents(Ring2_String_getBytes(Ring2_Context_get(), path), byteBuffer, &onReceiveByteBuffer)) {
    Ring2_jump();
  }
}

Ring2_String *
Machine_getFileContentsAsString
  (
    Ring2_String *path
  )
{
  Ring2_ByteBuffer* byteBuffer = Machine_getFileContentsAsByteBuffer(path);
  return Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object*, byteBuffer));
}
