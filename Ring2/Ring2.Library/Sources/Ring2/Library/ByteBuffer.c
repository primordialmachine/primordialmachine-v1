// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ByteBuffer.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/ByteBuffer.h"
#undef RING2_LIBRARY_PRIVATE


#include "Ring1/ByteBuffer.h"
#include "Ring1/Intrinsic/_Include.h"
#include "Ring1/Memory/_Include.h"
#include "Ring1/Status.h"


struct Ring2_ByteBuffer_Class {
  Machine_Object_Class __parent;
};

struct Ring2_ByteBuffer {
  Machine_Object __parent;
  Ring1_ByteBuffer byteBuffer;
};

static void
Ring2_ByteBuffer_construct
  (
    Ring2_ByteBuffer* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  if (Ring1_ByteBuffer_initialize(&self->byteBuffer)) {
    Ring2_jump();
  }
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring2_ByteBuffer_getType());
}

static void
Ring2_ByteBuffer_destruct
  (
    Ring2_ByteBuffer* self
  )
{
  Ring1_ByteBuffer_uninitialize(&self->byteBuffer);
}

MACHINE_DEFINE_CLASSTYPE(Ring2_ByteBuffer/*type*/,
                         Machine_Object/*parentType*/,
                         NULL/*visit*/,
                         &Ring2_ByteBuffer_construct/*construct*/,
                         &Ring2_ByteBuffer_destruct/*destruct*/,
                         NULL/*constructClasses*/,
                         NULL/*implementInterfaces*/)

Ring1_NoDiscardReturn() Ring2_ByteBuffer*
Ring2_ByteBuffer_create
  (
  )
{
  Machine_Type* ty = Ring2_ByteBuffer_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_ByteBuffer* self = Ring1_cast(Ring2_ByteBuffer*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

void
Ring2_ByteBuffer_appendBytes
  (
    Ring2_ByteBuffer* self,
    char const* p,
    int64_t n
  )
{
  /**@todo Ring1_ByteBuffer_appendBytes should provide an API call for n of type int64_t.*/
  if (n < 0 || n > SIZE_MAX) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Ring1_ByteBuffer_appendBytes(&self->byteBuffer, p, (size_t)n)) {
    Ring2_jump();
  }
}

void
Ring2_ByteBuffer_prependBytes
  (
    Ring2_ByteBuffer* self,
    char const* p,
    int64_t n
  )
{
  /**@todo Ring1_ByteBuffer_appendBytes should provide an API call for n of type int64_t.*/
  if (n < 0 || n > SIZE_MAX) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Ring1_ByteBuffer_prependBytes(&self->byteBuffer, p, (size_t)n)) {
    Ring2_jump();
  }
}

void
Ring2_ByteBuffer_insertBytesAt
  (
    Ring2_ByteBuffer* self,
    int64_t i,
    char const* p,
    int64_t n
  )
{
  /**@todo Ring1_ByteBuffer_appendBytes should provide an API call for i and n of type int64_t.*/
  if (i < 0 || i > SIZE_MAX) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (n < 0 || n > SIZE_MAX) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Ring1_ByteBuffer_insertBytesAt(&self->byteBuffer, (size_t)i, p, (size_t)n)) {
    Ring2_jump();
  }
}

void
Ring2_ByteBuffer_clear
  (
    Ring2_ByteBuffer* self
  )
{
  Ring1_ByteBuffer_clear(&self->byteBuffer);
}

char const*
Ring2_ByteBuffer_getBytes
  (
    Ring2_ByteBuffer const* self
  )
{
  char const* bytes;
  if (Ring1_ByteBuffer_getBytes(&bytes, &self->byteBuffer)) {
    Ring2_jump();
  }
  return bytes;
}

int64_t
Ring2_ByteBuffer_getNumberOfBytes
  (
    Ring2_ByteBuffer const* self
  )
{
  /** @todo Ensure that Ring1_ByteBuffer_getNumbeOfBytes also returns int64_t. */
  size_t numberOfBytes;
  if (Ring1_ByteBuffer_getNumberOfBytes(&numberOfBytes, &self->byteBuffer)) {
    Ring2_jump();
  }
  /** @todo Remove cast when int64_t is used. */
  return (int64_t)numberOfBytes;
}

Ring2_Boolean
Ring2_ByteBuffer_compareBytes
  (
    Ring2_ByteBuffer const* self,
    char const* p,
    int64_t n
  )
{
  int64_t numberOfBytes = Ring2_ByteBuffer_getNumberOfBytes(self);
  char const* bytes = Ring2_ByteBuffer_getBytes(self);
  if (n != numberOfBytes) {
    return false;
  }
  int temporary;
  Ring1_Memory_compare(&temporary, bytes, (size_t)numberOfBytes, p, (size_t)n, Ring1_Memory_Compare_Lexicographic);
  return !temporary;
}
