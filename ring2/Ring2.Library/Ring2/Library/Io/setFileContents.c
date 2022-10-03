// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/setFileContents.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Io/setFileContents.h"


#include "Ring1/Memory.h"
#include "Ring2/Library/Io/_FileMapping.h"


void
Machine_setFileContents
  (
    Ring2_String* path,
    Machine_ByteBuffer* bytes
  )
{
  _Machine_FileMapping fileMapping;
  _Machine_FileMapping_openWrite(&fileMapping, path, Machine_ByteBuffer_getNumberOfBytes(bytes));
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring1_Memory_copyFast(fileMapping.bytes, Machine_ByteBuffer_getBytes(bytes),
                          Machine_ByteBuffer_getNumberOfBytes(bytes));
    Ring2_popJumpTarget();
    _Machine_FileMapping_close(&fileMapping);
  }
  else {
    Ring2_popJumpTarget();
    _Machine_FileMapping_close(&fileMapping);
    Ring2_jump();
  }
}
