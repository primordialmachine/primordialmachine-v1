/// @file Runtime/ByteBuffer.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/ByteBuffer.h"

#include "Ring1/ByteBuffer.h"
#include "Ring1/Status.h"
#include "Ring2/_Include.h"
#include "Runtime/Object/Object.h"
#include "Runtime/Value.h"

struct Machine_ByteBuffer_Class {
  Machine_Object_Class __parent;
};

struct Machine_ByteBuffer {
  Machine_Object __parent;
  Ring1_ByteBuffer byteBuffer;
};

static void Machine_ByteBuffer_construct(Machine_ByteBuffer* self, size_t numberOfArguments,
                                         Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  if (Ring1_ByteBuffer_initialize(&self->byteBuffer)) {
    Ring2_jump();
  }
  Machine_setClassType((Machine_Object*)self, Machine_ByteBuffer_getType());
}

static void Machine_ByteBuffer_destruct(Machine_ByteBuffer* self) {
  Ring1_ByteBuffer_uninitialize(&self->byteBuffer);
}

MACHINE_DEFINE_CLASSTYPE(Machine_ByteBuffer, Machine_Object, NULL, &Machine_ByteBuffer_construct,
                         &Machine_ByteBuffer_destruct, NULL, NULL)

Machine_ByteBuffer* Machine_ByteBuffer_create() {
  Machine_ClassType* ty = Machine_ByteBuffer_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Ring2_Void_Void } };
  Machine_ByteBuffer* self
      = (Machine_ByteBuffer*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_ByteBuffer_appendBytes(Machine_ByteBuffer* self, char const* p, size_t n) {
  if (Ring1_ByteBuffer_appendBytes(&self->byteBuffer, p, n)) {
    Ring2_jump();
  }
}

void Machine_ByteBuffer_prependBytes(Machine_ByteBuffer* self, char const* p, size_t n) {
  if (Ring1_ByteBuffer_prependBytes(&self->byteBuffer, p, n)) {
    Ring2_jump();
  }
}

void Machine_ByteBuffer_insertBytesAt(Machine_ByteBuffer* self, size_t i, char const* p, size_t n) {
  if (Ring1_ByteBuffer_insertBytesAt(&self->byteBuffer, i, p, n)) {
    Ring2_jump();
  }
}

void Machine_ByteBuffer_clear(Machine_ByteBuffer* self) {
  Ring1_ByteBuffer_clear(&self->byteBuffer);
}

char const* Machine_ByteBuffer_getBytes(Machine_ByteBuffer const* self) {
  char const* bytes;
  if (Ring1_ByteBuffer_getBytes(&bytes, &self->byteBuffer)) {
    Ring2_jump();
  }
  return bytes;
}

size_t Machine_ByteBuffer_getNumberOfBytes(Machine_ByteBuffer const* self) {
  size_t numberOfBytes;
  if (Ring1_ByteBuffer_getNumberOfBytes(&numberOfBytes, &self->byteBuffer)) {
    Ring2_jump();
  }
  return numberOfBytes;
}

Ring2_Boolean Machine_ByteBuffer_compareBytes(Machine_ByteBuffer const* self, char const* p,
                                              size_t n) {
  size_t numberOfBytes = Machine_ByteBuffer_getNumberOfBytes(self);
  char const* bytes = Machine_ByteBuffer_getBytes(self);
  if (n != numberOfBytes) {
    return false;
  }
  int temporary;
  Ring1_Memory_compare(&temporary, bytes, numberOfBytes, p, n, Ring1_Memory_Compare_Lexicographic);
  return !temporary;
}
