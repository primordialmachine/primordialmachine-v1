#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/ByteBufferReader.h"



#include "Machine.h"
#include "Runtime/Arguments.h"



struct Machine_ByteBufferReader_Class {
  Machine_Object_Class __parent;
};

struct Machine_ByteBufferReader {
  Machine_Object __parent;

  Machine_ByteBuffer* byteBuffer;
  size_t position;
};


static void Machine_ByteBufferReader_visit(Machine_ByteBufferReader* self) {
  if (self->byteBuffer) {
    Machine_Gc_visit(self->byteBuffer);
  }
}

void Machine_ByteBufferReader_construct(Machine_ByteBufferReader* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->byteBuffer = (Machine_ByteBuffer *)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0, Machine_ByteBuffer_getType());
  self->position = 0;
  Machine_setClassType((Machine_Object*)self, Machine_ByteBufferReader_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_ByteBufferReader, Machine_Object, NULL,
                         &Machine_ByteBufferReader_construct, NULL, &Machine_ByteBufferReader_visit,
                         NULL)

Machine_ByteBufferReader* Machine_ByteBufferReader_create(Machine_ByteBuffer* byteBuffer) {
  Machine_ClassType* ty = Machine_ByteBufferReader_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Machine_Value arguments[1];
  Machine_Value_setObject(&arguments[0], (Machine_Object*)byteBuffer);
  Machine_ByteBufferReader* self = (Machine_ByteBufferReader*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

size_t Machine_ByteBufferReader_getPosition(Machine_ByteBufferReader* self) {
  return self->position;
}

void Machine_ByteBufferReader_read(Machine_ByteBufferReader* self, char* p, size_t n, size_t* m) {
  size_t l = Machine_ByteBuffer_getNumberOfBytes(self->byteBuffer);
  l = l < n ? l : n;
  Machine_Eal_Memory_copy(p, Machine_ByteBuffer_getBytes(self->byteBuffer) + self->position, l, false);
  *m = l;
}
