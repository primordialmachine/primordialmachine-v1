/// @file Runtime/StringBuffer.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/StringBuffer.h"

#include "Runtime/ByteBuffer.h"
#include "Runtime/Object/Object.h"
#include "Runtime/String.h"
#include "Runtime/Value.h"

struct Machine_StringBuffer_Class {
  Machine_Object_Class __parent;
};

struct Machine_StringBuffer {
  Machine_Object __parent;

  Machine_ByteBuffer* byteBuffer;
};

static void Machine_StringBuffer_visit(Machine_StringBuffer* self) {
  if (self->byteBuffer) {
    Machine_Gc_visit(self->byteBuffer);
  }
}

static Ring2_String* Machine_StringBuffer_toStringImpl(Machine_StringBuffer const* self) {
  return Machine_String_create(Machine_ByteBuffer_getBytes(self->byteBuffer),
                               Machine_ByteBuffer_getNumberOfBytes(self->byteBuffer));
}

static void Machine_StringBuffer_constructClass(Machine_StringBuffer_Class* self) {
  ((Machine_Object_Class*)self)->toString
      = (Ring2_String * (*)(Machine_Object const*)) & Machine_StringBuffer_toStringImpl;
}

static void Machine_StringBuffer_construct(Machine_StringBuffer* self, size_t numberOfArguments,
                                           Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->byteBuffer = Machine_ByteBuffer_create();
  Machine_setClassType((Machine_Object*)self, Machine_StringBuffer_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_StringBuffer, Machine_Object, &Machine_StringBuffer_visit,
                         &Machine_StringBuffer_construct, NULL,
                         &Machine_StringBuffer_constructClass, NULL)

Machine_StringBuffer* Machine_StringBuffer_create() {
  Machine_ClassType* ty = Machine_StringBuffer_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Ring2_Void_Void } };
  Machine_StringBuffer* self
      = (Machine_StringBuffer*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_StringBuffer_appendBytes(Machine_StringBuffer* self, char const* p, size_t n) {
  Machine_ByteBuffer_appendBytes(self->byteBuffer, p, n);
}

void Machine_StringBuffer_appendString(Machine_StringBuffer* self, Ring2_String const* s) {
  Machine_ByteBuffer_appendBytes(self->byteBuffer, Machine_String_getBytes(s),
                                 Machine_String_getNumberOfBytes(s));
}

void Machine_StringBuffer_prependBytes(Machine_StringBuffer* self, const char* p, size_t n) {
  Machine_ByteBuffer_prependBytes(self->byteBuffer, p, n);
}

void Machine_StringBuffer_prependString(Machine_StringBuffer* self, Ring2_String const* s) {
  Machine_ByteBuffer_prependBytes(self->byteBuffer, Machine_String_getBytes(s),
                                  Machine_String_getNumberOfBytes(s));
}

void Machine_StringBuffer_insertBytesAt(Machine_StringBuffer* self, size_t i, const char* p,
                                        size_t n) {
  Machine_ByteBuffer_insertBytesAt(self->byteBuffer, i, p, n);
}

void Machine_StringBuffer_clear(Machine_StringBuffer* self) {
  Machine_ByteBuffer_clear(self->byteBuffer);
}
