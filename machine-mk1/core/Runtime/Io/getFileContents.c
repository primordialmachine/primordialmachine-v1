/// @file Runtime/Io/getFileContents.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Io/getFileContents.h"

#include "Runtime/Io/_FileMapping.h"

Machine_ByteBuffer* Machine_getFileContents(Machine_String* path) {
  path = Machine_String_concatenate(path, Machine_String_create("", 1));
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
