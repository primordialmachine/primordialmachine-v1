// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/Logger.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_PRIVATE (1)
#include "Ring1/Log/Logger.h"
#undef RING1_PRIVATE

void
Ring1_Logger_ref
  (
    Ring1_Logger *self
  )
{ 
  self->referenceCount++;
}
  
void
Ring1_Logger_unref
  (
    Ring1_Logger *self
  )
{
  if (0 == --self->referenceCount) {
    if (self->destruct) {
      self->destruct(self);
    }
    free(self);
  }
}

Ring1_CheckReturn() Ring1_Result
Ring1_Logger_construct
  (
    Ring1_Logger *self
  )
{
  self->referenceCount = 1;
  self->write = NULL;
  self->destruct = &Ring1_Logger_destruct;
  return Ring1_Result_Success;
}

void
Ring1_Logger_destruct
  (
    Ring1_Logger* self
  )
{}

Ring1_CheckReturn() Ring1_Result
Ring1_Logger_write
  (
    Ring1_Logger* self,
    char const* bytes,
    size_t numberOfBytes
  )
{ return self->write(self, bytes, numberOfBytes); }
