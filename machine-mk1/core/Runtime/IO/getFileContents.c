/// @file Runtime/IO/getFileContents.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/IO/getFileContents.h"

#include "Runtime/IO/_FileMapping.h"

Machine_ByteBuffer* Machine_getFileContents(Machine_String* path) {
  path = Machine_String_concatenate(path, Machine_String_create("", 1));
  Machine_ByteBuffer* byteBuffer = Machine_ByteBuffer_create();
  _Machine_FileMapping fileMapping;
  _Machine_FileMapping_openRead(&fileMapping, path);
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_ByteBuffer_appendBytes(byteBuffer, fileMapping.bytes, fileMapping.numberOfBytes);
    Machine_popJumpTarget();
    _Machine_FileMapping_close(&fileMapping);
  } else {
    Machine_popJumpTarget();
    _Machine_FileMapping_close(&fileMapping);
    Machine_jump();
  }
  return byteBuffer;
}
