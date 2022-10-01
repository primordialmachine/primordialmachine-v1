// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/StringBuffer.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/StringBuffer.h"
#undef RING2_LIBRARY_PRIVATE


#include <stdio.h>
#include "Ring1/Memory.h"
#include "Ring1/ByteBuffer.h"
#include "Ring1/Status.h"


struct Machine_StringBuffer_Class {
  Machine_Object_Class _parent;
};

struct Machine_StringBuffer {
  Machine_Object _parent;
  Ring1_ByteBuffer* pimpl;
};

static Ring2_String*
toString
  (
    Ring2_Context *context,
    Machine_StringBuffer* self
  );

static void
Machine_StringBuffer_constructClass
  (
    Machine_StringBuffer_Class *self
  );

static void
Machine_StringBuffer_destruct
  (
    Machine_StringBuffer* self
  );

MACHINE_DEFINE_CLASSTYPE(Machine_StringBuffer /*type*/,
                         Machine_Object /*parentType*/,
                         NULL /*visit*/,
                         &Machine_StringBuffer_construct /*construct*/,
                         &Machine_StringBuffer_destruct /*destruct*/,
                         &Machine_StringBuffer_constructClass /*constructClass*/,
                         NULL)

static Ring2_String*
toString
  (
    Ring2_Context *context,
    Machine_StringBuffer* self
  )
{
  char const* bytes;
  size_t numberOfBytes;
  if (Ring1_ByteBuffer_getBytes(&bytes, self->pimpl))
  { Ring2_jump(); }
  if (Ring1_ByteBuffer_getNumberOfBytes(&numberOfBytes, self->pimpl))
  { Ring2_jump(); }
  return Ring2_String_create(Ring2_Context_get(), bytes, numberOfBytes);
}

static void
Machine_StringBuffer_constructClass
  (
    Machine_StringBuffer_Class *self
  )
{
  Ring1_cast(Machine_Object_Class*, self)->toString = (Ring2_String *(*)(Ring2_Context *, Machine_Object const *))&toString;
}

static void
Machine_StringBuffer_destruct
  (
    Machine_StringBuffer* self
  )
{
  if (self->pimpl) {
    Ring1_ByteBuffer_uninitialize(self->pimpl);
    Ring1_Memory_deallocate(self->pimpl);
    self->pimpl = NULL;
  }
}

void
Machine_StringBuffer_construct
  (
    Machine_StringBuffer *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  Ring1_ByteBuffer* pimpl;
  if (Ring1_Memory_allocate(&pimpl, sizeof(Ring1_ByteBuffer))) {
    fprintf(stderr, "%s:%d: allocation failed\n", __FILE__, __LINE__);
    Ring2_jump();
  }
  if (Ring1_ByteBuffer_initialize(pimpl)) {
    Ring1_Memory_deallocate(pimpl);
    fprintf(stderr, "%s:%d: initialization failed\n", __FILE__, __LINE__);
    Ring2_jump();
  }
  self->pimpl = pimpl;
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Machine_StringBuffer_getType());
}

Machine_StringBuffer *
Machine_StringBuffer_create
  (
  )
{
  Machine_ClassType* ty = Machine_StringBuffer_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[1] = { Ring2_Value_StaticInitializerVoid() };
  Machine_StringBuffer* self = (Machine_StringBuffer*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void
Machine_StringBuffer_appendByte
  (
    Machine_StringBuffer* self,
    char byte
  )
{
  if (Ring1_ByteBuffer_appendByte(self->pimpl, byte))
  { Ring2_jump(); }
}

void
Machine_StringBuffer_appendBytes
  (
    Machine_StringBuffer* self,
    char const* bytes,
    size_t numberOfBytes
  )
{
  if (Ring1_ByteBuffer_appendBytes(self->pimpl, bytes, numberOfBytes))
  { Ring2_jump(); }
}

void
Machine_StringBuffer_appendString
  (
    Machine_StringBuffer* self,
    Ring2_String* string
  )
{ 
  Machine_StringBuffer_appendBytes(self, Ring2_String_getBytes(Ring2_Context_get(), string),
                                   (size_t)Ring2_String_getNumberOfBytes(Ring2_Context_get(), string));
}

void
Machine_StringBuffer_clear
  (
    Machine_StringBuffer* self
  )
{ Ring1_ByteBuffer_clear(self->pimpl); }

const char*
Machine_StringBuffer_getBytes
  (
    Machine_StringBuffer* self
  )
{
  char const* bytes;
  if (Ring1_ByteBuffer_getBytes(&bytes, self->pimpl))
  { Ring2_jump(); }
  return bytes;
}

size_t
Machine_StringBuffer_getNumberOfBytes
  (
    Machine_StringBuffer* self
  )
{ 
  size_t numberOfBytes;
  if (Ring1_ByteBuffer_getNumberOfBytes(&numberOfBytes, self->pimpl))
  { Ring2_jump(); }
  return numberOfBytes;
}
