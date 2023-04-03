// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ByteBufferReader.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/ByteBufferReader.h"
#undef RING2_LIBRARY_PRIVATE


#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/CallArguments.h"
#undef RING2_LIBRARY_PRIVATE
#include "Ring1/All/_Include.h"


struct Ring2_ByteBufferReader_Class {
  Machine_Object_Class __parent;
};

struct Ring2_ByteBufferReader {
  Machine_Object __parent;

  Ring2_ByteBuffer* byteBuffer;
  int64_t position;
};

static void
Ring2_ByteBufferReader_visit
  (
    Ring2_ByteBufferReader* self
  )
{
  if (self->byteBuffer) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->byteBuffer);
  }
}

void
Ring2_ByteBufferReader_construct
  (
    Ring2_ByteBufferReader* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*,self), numberOfArguments, arguments);
  self->byteBuffer = Ring1_cast(Ring2_ByteBuffer*,
                               Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                     arguments,
                                                                     0,
                                                                     Ring2_ByteBuffer_getType()));
  self->position = 0;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring2_ByteBufferReader_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring2_ByteBufferReader,
                         Machine_Object, NULL,
                         &Ring2_ByteBufferReader_construct,
                         NULL,
                         &Ring2_ByteBufferReader_visit,
                         NULL)

Ring1_NoDiscardReturn() Ring2_ByteBufferReader*
Ring2_ByteBufferReader_create
  (
    Ring2_ByteBuffer* byteBuffer
  )
{
  Machine_Type* ty = Ring2_ByteBufferReader_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,byteBuffer));
  Ring2_ByteBufferReader* self = Ring1_cast(Ring2_ByteBufferReader*,
                                            Machine_allocateClassObject(ty,
                                                                        NUMBER_OF_ARGUMENTS,
                                                                        arguments));
  return self;
}

Ring1_NoDiscardReturn() int64_t
Ring2_ByteBufferReader_getPosition
  (
    Ring2_ByteBufferReader* self
  )
{ return self->position; }

void
Ring2_ByteBufferReader_read
  (
    Ring2_ByteBufferReader* self,
    char* p,
    int64_t n,
    int64_t* m
  )
{
  if (!p || n < 0) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  int64_t l = Ring2_ByteBuffer_getNumberOfBytes(self->byteBuffer);
  l = l < n ? l : n;
  Ring1_Memory_copyFast(p, Ring2_ByteBuffer_getBytes(self->byteBuffer) + self->position, l);
  *m = l;
}
