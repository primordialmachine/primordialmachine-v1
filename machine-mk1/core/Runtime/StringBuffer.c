#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/StringBuffer.h"


#include "Runtime/ByteBuffer.h"


struct Machine_StringBuffer {
  Machine_Object parent;
  Machine_ByteBuffer* byteBuffer;
};

static void Machine_StringBuffer_construct(Machine_StringBuffer* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->byteBuffer = Machine_ByteBuffer_create();
  Machine_setClassType(self, Machine_StringBuffer_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_StringBuffer)
MACHINE_DEFINE_CLASSTYPE_EX(Machine_StringBuffer, Machine_Object, NULL, &Machine_StringBuffer_construct, NULL)

Machine_StringBuffer* Machine_StringBuffer_create() {
  Machine_ClassType* ty = Machine_StringBuffer_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
  Machine_StringBuffer* self = (Machine_StringBuffer *)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_StringBuffer_appendBytes(Machine_StringBuffer* self, const char* p, size_t n) {
  Machine_ByteBuffer_appendBytes(self->byteBuffer, p, n);
}

void Machine_StringBuffer_clear(Machine_StringBuffer* self) {
  Machine_ByteBuffer_clear(self->byteBuffer);
}

Machine_String *Machine_StringBuffer_toString(Machine_StringBuffer* self) {
  return Machine_String_create(Machine_ByteBuffer_getBytes(self->byteBuffer), Machine_ByteBuffer_getNumberOfBytes(self->byteBuffer));
}
