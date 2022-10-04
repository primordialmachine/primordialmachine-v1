// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/getFileContents.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Io/getFileContents.h"


#include "Ring1/FileSystem.h"
#include "Ring2/Library/Io/Initialize.h"


static Ring1_Result
onReceive
  (
    Machine_ByteBuffer *self,
    const char *p,
    size_t n
  )
{
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_ByteBuffer_appendBytes(self, p, n);
    Ring2_popJumpTarget();
    return Ring1_Result_Success;
  } else {
    Ring2_popJumpTarget();
    return Ring1_Result_Failure;
  }
}

Machine_ByteBuffer*
Machine_getFileContents
  (
    Ring2_String* path
  )
{
  Machine_Io_initialize();
  path = Ring2_String_concatenate(Ring2_Context_get(), path, Ring2_String_create(Ring2_Context_get(), "", 1));
  Machine_ByteBuffer* byteBuffer = Machine_ByteBuffer_create();
  if (Ring1_FileSystem_receiveFileContents(Ring2_String_getBytes(Ring2_Context_get(), path), byteBuffer, &onReceive)) {
    Ring2_jump();
  }
  return byteBuffer;
}
