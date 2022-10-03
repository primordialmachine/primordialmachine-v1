// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/getFileContents.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Io/getFileContents.h"


#include "Ring1/Memory.h"
#include "Ring2/Library/Io/_FileMapping.h"


Machine_ByteBuffer*
Machine_getFileContents
  (
    Ring2_String* path
  )
{
  path = Ring2_String_concatenate(Ring2_Context_get(), path, Ring2_String_create(Ring2_Context_get(), "", 1));
  Machine_ByteBuffer* byteBuffer = Machine_ByteBuffer_create();
  _Machine_FileMapping fileMapping;
  _Machine_FileMapping_openRead(&fileMapping, path);
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_ByteBuffer_appendBytes(byteBuffer, fileMapping.bytes, fileMapping.numberOfBytes);
    Ring2_popJumpTarget();
    _Machine_FileMapping_close(&fileMapping);
  } else {
    Ring2_popJumpTarget();
    _Machine_FileMapping_close(&fileMapping);
    Ring2_jump();
  }
  return byteBuffer;
}
