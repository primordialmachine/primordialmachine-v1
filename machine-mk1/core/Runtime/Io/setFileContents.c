/// @file Runtime/Io/setFileContents.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Io/setFileContents.h"

#include "Runtime/Io/_FileMapping.h"

void Machine_setFileContents(Machine_String* path, Machine_ByteBuffer* bytes) {
  _Machine_FileMapping fileMapping;
  _Machine_FileMapping_openWrite(&fileMapping, path, Machine_ByteBuffer_getNumberOfBytes(bytes));
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    memcpy(fileMapping.bytes, Machine_ByteBuffer_getBytes(bytes), Machine_ByteBuffer_getNumberOfBytes(bytes));
    Machine_popJumpTarget();
    _Machine_FileMapping_close(&fileMapping);
  }
  else {
    Machine_popJumpTarget();
    _Machine_FileMapping_close(&fileMapping);
    Machine_jump();
  }
}
